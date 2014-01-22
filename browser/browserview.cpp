#include <QDebug>
#include <QWebFrame>

#include "browserview.h"

BrowserView::BrowserView()
{
    if (!this->scene()) {
        this->setScene(new QGraphicsScene());
    }
    this->scene()->addItem (&m_webview);

    connect(&m_webview, SIGNAL (loadStarted()),      this, SIGNAL (pageLoadStarted ()));
    connect(&m_webview, SIGNAL (loadFinished(bool)), this, SIGNAL (pageLoadFinished (bool)));
    connect(&m_webview, SIGNAL (loadProgress(int)),  this, SLOT   (loadProgress(int)));
}

bool BrowserView::load(const QString &a_Url)
{
    m_webview.load(a_Url);
    return true;
}

void BrowserView::loadProgress(int progress)
{
    m_currentProgress = progress;
    emit pageLoadProgress (progress);
}
void BrowserView::scroll (BrowserView::ScrollDirection dir, BrowserView::ScrollType type)
{
    int stepSize = 50;
    int xMultiplier = 0;
    int yMultiplier = 0;

    switch (dir) {
    case BrowserView::SCROLLDIRECTION_UP:
        yMultiplier = -1;
        break;
    case BrowserView::SCROLLDIRECTION_DOWN:
        yMultiplier = 1;
        break;
    case BrowserView::SCROLLDIRECTION_RIGHT:
        xMultiplier = 1;
        break;
    case BrowserView::SCROLLDIRECTION_LEFT:
        xMultiplier = -1;
        break;
    default:
        qDebug() << "Invalid direction";
        break;
    }

    if (type == BrowserView::SCROLLTYPE_PAGESTEP)
        stepSize= this->height();

    if (m_webview.page() && m_webview.page()->mainFrame())
        m_webview.page()->mainFrame()->scroll(stepSize*xMultiplier,
                                              stepSize*yMultiplier);
}

void BrowserView::resizeEvent (QResizeEvent *event) {
    int w = event->size().width();
    int h = event->size().height();
    m_webview.setGeometry (QRect(0,0,w,h));
}
