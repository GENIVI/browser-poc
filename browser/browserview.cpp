/**
 * Copyright (C) 2014, Pelagicore
 *
 * Author: Jonatan Pålsson <jonatan.palsson@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <QDebug>
#include <QWebFrame>
#include <QWebPage>
#include <QCoreApplication>
#include <QTemporaryFile>
#include <QSemaphore>
#include <QWebSettings>

#include "browserview.h"
#include "cachemanager.h"
#include "../common/browserdefs.h"
#include "browserpage.h"
#include "userinput.h"
#include "browserconfig.h"

BrowserView::BrowserView(cachemanager *cm, userinput *uip)
    : m_cacheManager (cm)
{
    QString startPage;
    m_cacheManager = cm;
    if (!this->scene()) {
        this->setScene(new QGraphicsScene());
    }
    this->scene()->addItem (&m_webview);

    QWebSettings::setIconDatabasePath(".");

    m_webview.setPage(new BrowserPage(this, uip));

    m_webview.page()->setNetworkAccessManager(cm->getNetworkAccessManager());

    startPage = BrowserConfig::instance()->getValue<QString>(BrowserConfig::CONFIG_STARTPAGE);
    if (startPage.compare("") == 0)
        startPage = "http://www.bmw.com";

    this->load(startPage);

    this->installEventFilter(this);

    setWindowFlags(Qt::FramelessWindowHint);
    m_webview.page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(&m_webview, SIGNAL (loadStarted()),             this, SIGNAL (pageLoadStarted ()));
    connect(&m_webview, SIGNAL (statusBarMessage(QString)), this, SIGNAL (onStatusTextChanged(QString)));
    connect(&m_webview, SIGNAL (loadFinished(bool)),        this, SLOT   (loadFinished (bool)));
    connect(&m_webview, SIGNAL (loadProgress(int)),         this, SLOT   (loadProgress(int)));
    connect(&m_webview, SIGNAL (urlChanged(QUrl)),          this, SLOT   (urlChanged(QUrl)));
    connect(&m_webview, SIGNAL (titleChanged(QString)),     this, SLOT   (titleChanged(QString)));
    connect(&m_webview, SIGNAL (linkClicked(QUrl)),         this, SLOT   (linkClicked(QUrl)));

    connect(m_webview.page(), SIGNAL (selectionChanged(void)), this, SIGNAL(onSelectionChanged(void)));
    connect(m_webview.page(), SIGNAL (linkHovered(const QString&,const QString&,const QString&)), this, SIGNAL(onLinkHovered(QString)));
    connect(m_webview.page()->mainFrame(), SIGNAL (contentsSizeChanged(const QSize &)), this, SLOT (contentSizeChanged(const QSize&)));
    connect(&m_webview, SIGNAL (iconChanged()),             this, SIGNAL (onFaviconReceived()));

    connect(&m_inputHandler, SIGNAL (onInputText(QString, QString, int, int, int, int, int)), 
        this, SIGNAL (onInputText(QString, QString, int, int, int, int, int)));
    connect(&m_inputHandler, SIGNAL(onScroll(uint,uint)), this, SLOT(scrollPositionChanged(uint,uint)));
    connect(&m_inputHandler, SIGNAL(onSelect(const QString &, const conn::brw::SelectableOptionList &, bool)), this, SIGNAL(onSelect(const QString &, const conn::brw::SelectableOptionList &, bool)));

}

bool BrowserView::load(const QString &a_Url)
{
    if (m_cacheManager) {
        QNetworkRequest req = QNetworkRequest(QUrl(a_Url));
        req.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                         m_cacheManager->getCacheLoadControl());
        m_webview.load(req);
    } else {
        qDebug() << "No cacheManager present, defaulting to load(url)";
        m_webview.load(a_Url);
    }

    BrowserConfig::instance()->setValue<QString>(BrowserConfig::CONFIG_STARTPAGE, a_Url);
    return true;
}

void BrowserView::loadProgress(int progress)
{
    m_currentProgress = progress;
    emit pageLoadProgress (progress);
}

void BrowserView::loadFinished(bool ok)
{
    // Inject some JS into the page, and hook it up to an object of ours, this
    // allows us to detect when the user toggles an input field

    m_webview.page()->mainFrame()->addToJavaScriptWindowObject("inputHandler", &m_inputHandler);

    m_webview.page()->mainFrame()->evaluateJavaScript(
    "(function() {"
        "var pocCurrentElement = null;"
        "document.addEventListener('focus', function(e){"
        "    if (pocCurrentElement != e.target) {"
        "       window.inputHandler.setCurrentFocus(e.target);"
        "       pocCurrentElement = e.target;"
        "    }"
        "}, true);"
        "document.addEventListener('focusout', function(e){"
        "    pocCurrentElement = e.relatedTarget;"
        "}, true);"
    "})()"
    );

    m_webview.page()->mainFrame()->evaluateJavaScript(
    "document.addEventListener('scroll', function(){"
    "    window.inputHandler.setScrollPosition(window.pageXOffset, window.pageYOffset);"
    "}, true);");

    emit pageLoadFinished (ok);
}

void BrowserView::scroll (conn::brw::SCROLL_DIRECTION dir, conn::brw::SCROLL_TYPE type)
{
    int stepSize = 50;
    int xMultiplier = 0;
    int yMultiplier = 0;
    Qt::Key key(Qt::Key_Tab);

    switch (dir) {
    case conn::brw::SD_TOP:
        yMultiplier = -1;
        key = Qt::Key_Backtab;
        break;
    case conn::brw::SD_BOTTOM:
        yMultiplier = 1;
        key = Qt::Key_Tab;
        break;
    case conn::brw::SD_RIGHT:
        xMultiplier = 1;
        key = Qt::Key_Tab;
        break;
    case conn::brw::SD_LEFT:
        xMultiplier = -1;
        key = Qt::Key_Backtab;
        break;
    default:
        qDebug() << "Invalid direction";
        break;
    }

    if (type == conn::brw::ST_PAGE)
        stepSize= this->height();

    if (type == conn::brw::ST_LINK) {
        QKeyEvent event(QEvent::KeyPress, key, Qt::NoModifier);
        QCoreApplication::sendEvent(m_webview.page(), &event);
    } else {
        if (m_webview.page() && m_webview.page()->mainFrame())
            m_webview.page()->mainFrame()->scroll(stepSize*xMultiplier,
                                                  stepSize*yMultiplier);
    }
}

void BrowserView::inputText (QString input)
{
    QInputMethodEvent event;
    event.setCommitString(input);
    QCoreApplication::sendEvent(m_webview.page(), &event);
}

void BrowserView::resizeEvent (QResizeEvent *event) {
    int w = event->size().width();
    int h = event->size().height();
    m_webview.setGeometry (QRect(0,0,w,h));
}

QSize BrowserView::contentSize()
{
    return this->viewport()->size();
}

void BrowserView::urlChanged (QUrl url)
{
    QString strUrl = url.toString();
    if (strUrl.compare("") != 0)
        emit onUrlChanged (strUrl);
}

void BrowserView::titleChanged (QString title)
{
    if (title.compare("") != 0)
        emit onTitleChanged (title);
}

void BrowserView::linkClicked(QUrl url) {
    QString strUrl = url.toString();
    this->load(strUrl);
    emit onLinkClicked(strUrl);
}

bool BrowserView::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type()      == QEvent::Show)
        emit onVisibilityChanged(true);
    else if (event->type() == QEvent::Hide)
        emit onVisibilityChanged(false);

    return QGraphicsView::eventFilter(obj, event);
}

void BrowserView::setZoomFactor(double factor)
{
    m_webview.setZoomFactor(factor);
    emit onZoomFactorChanged (factor);
}

double BrowserView::getZoomFactor()
{
    return m_webview.zoomFactor();
}

void BrowserView::scrollPositionChanged(uint x, uint y)
{
    m_scrollPositionX = x;
    m_scrollPositionY = y;
    emit onScrollPositionChanged(x,y);
}

void BrowserView::setScrollPosition(uint x, uint y)
{
    QString cmd = QString("window.scrollTo(%1,%2);").arg(QString::number(x), QString::number(y));
    m_webview.page()->mainFrame()->evaluateJavaScript(cmd);
    m_scrollPositionX = x;
    m_scrollPositionY = y;
}

void BrowserView::getScrollPosition(uint &x, uint &y)
{
    x = m_scrollPositionX;
    y = m_scrollPositionY;
}

QString BrowserView::createScreenshot(QString url) {
    WebPageWaiter waiter;
    QWebPage wp;
    QSize renderSize(640,480);

    connect(&wp, SIGNAL(loadFinished(bool)), &waiter, SLOT (loadFinished(void)));

    wp.mainFrame()->load(QUrl(url));
    wp.setViewportSize(renderSize);
    wp.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    wp.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);

    for (int i = 0; i < 100; i++) {
        waiter.finishedSem.tryAcquire(1,10);
        QCoreApplication::processEvents();
    }

    QImage *image = new QImage(renderSize,
                               QImage::Format_ARGB32);
    QPainter *painter = new QPainter(image);
    QTemporaryFile outFile("XXXXXX.png");
    outFile.setAutoRemove(false);
    outFile.open();
    wp.mainFrame()->render(painter);

    painter->end();
    image->save(&outFile, "PNG");
    outFile.close();
    return outFile.fileName();
}

QString BrowserView::getFaviconFilePath(QString url) {

    QIcon icon = QWebSettings::globalSettings()->iconForUrl(QUrl(url));
    if (icon.isNull())
        return "";

    QImage image = icon.pixmap(15).toImage();

    QTemporaryFile outFile("XXXXXX.png");
    outFile.setAutoRemove(false);
    outFile.open();

    image.save(&outFile, "PNG");
    outFile.close();

    return outFile.fileName();
}

void BrowserView::contentSizeChanged(const QSize &size) {
    emit onContentSizeChanged(size.width(), size.height());
}

void BrowserView::select() {
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    QCoreApplication::sendEvent(m_webview.page(), &event);
}
void BrowserView::activate() {
    this->setVisible(true);
}

void BrowserView::onSelectIndexes(QList<int> indexes) {
    for (int i = 0; i < indexes.size(); i++) {
        QString cmd = QString("document.activeElement.options[%1].selected = true").arg(
                                QString::number(indexes.at(i)));
        m_webview.page()->mainFrame()->evaluateJavaScript(cmd);
    }
}
