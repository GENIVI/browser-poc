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

#ifndef BROWSERVIEW_H
#define BROWSERVIEW_H

#include <QGraphicsWebView>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QWebElement>
#include <QDebug>
#include <QSemaphore>
#include <QNetworkAccessManager>

#include "cachemanager.h"
#include "../common/browserdefs.h"
#include "browserpage.h"
#include "userinput.h"

class InputHandler : public QObject {
Q_OBJECT
public:
    InputHandler () : m_textElements (new QStringList()) {
        *m_textElements << "date" << "datetime" << "datetime-local" << "email"
        << "month" << "number" << "password" << "range" << "tel" << "text"
        << "time" << "url" << "week";
    }
public slots:
    void setScrollPosition (const int &x, const int &y) {
        emit onScroll ((uint)x,(uint)y);
    }
    void setCurrentFocus (const QWebElement &elem) {
        QString attrType = elem.attribute("type", "text");
        if ((elem.tagName().compare("INPUT", Qt::CaseInsensitive) == 0 &&
                m_textElements->contains(attrType))
            ||
            elem.tagName().compare("TEXTAREA", Qt::CaseInsensitive) == 0)
        {
            emit onInputText (elem.attribute("name"), elem.attribute("value"),
                              elem.attribute("type", "0").toInt(),
                              elem.attribute("maxlength", "0").toInt(),
                              elem.attribute("max", "0").toInt(),
                              elem.attribute("min","0").toInt(),
                              elem.attribute("step","0").toInt());
        } else if (elem.tagName().compare("SELECT", Qt::CaseInsensitive) == 0){
            conn::brw::SelectableOptionList options;
            QList<QWebElement> elems;
            QWebElement first = elem.firstChild();
            QWebElement last  = elem.lastChild();

            conn::brw::SelectableOption o;
            o.strValue = first.toPlainText();
            options.append(o);
            elems.append(first);
            while (elems.last() != last) {
                conn::brw::SelectableOption o;
                o.strValue = elems.last().toPlainText();
                elems.append(elems.last().nextSibling());
                options.append(o);
            }

            qDebug() << "Options:" << options.size();
            emit onSelect(elem.attribute("name", ""), options, true);
        }
        m_elem = elem;
    }
    const QWebElement currentFocus () { return m_elem; }

signals:
    void onInputText(QString name, QString value, int type, int maxlength,
                     int max, int min, int step);
    void onScroll(uint x, uint y);
    void onSelect(const QString &, const conn::brw::SelectableOptionList &, bool);

private:
    QWebElement m_elem;
    QStringList *m_textElements;
};

class BrowserView : public QGraphicsView
{
     Q_OBJECT
public:
    BrowserView(cachemanager *, userinput *);
    bool load(const QString &a_Url);
    int getProgress() { return m_currentProgress; }
    QString getUrl() { return m_webview.url().toString(); }
    const QString getTitle() { return m_webview.title(); }
    void goBack() { m_webview.back(); }
    void goForward() { m_webview.forward(); }
    void pageReload() { m_webview.reload(); }
    void pageStop() { m_webview.stop(); }
    void scroll (conn::brw::SCROLL_DIRECTION dir, conn::brw::SCROLL_TYPE type);
    QSize contentSize();
    void setZoomFactor(double);
    double getZoomFactor();
    void getScrollPosition(uint&, uint&);
    void setScrollPosition(uint, uint);
    QString createScreenshot(QString url);
    QString getFaviconFilePath(QString url);
    void activate();
    void select();

signals:
    void pageLoadStarted();
    void pageLoadFinished(bool);
    void pageLoadProgress(int);
    void onInputText(QString name, QString value, int type, int maxlength,
                     int max, int min, int step);
    void onUrlChanged(QString url);
    void onTitleChanged(QString title);
    void onLinkClicked(QString);
    void onSelectionChanged();
    void onStatusTextChanged(QString);
    void onVisibilityChanged(bool);
    void onScrollPositionChanged(uint,uint);
    void onZoomFactorChanged(double);
    void onLinkHovered(QString);
    void onActionStateChanged(uint);
    void onContentSizeChanged(uint, uint);
    void onFaviconReceived();
    void onSelect(const QString &, const conn::brw::SelectableOptionList &, bool);

protected:
    virtual void resizeEvent (QResizeEvent *event);
    virtual bool eventFilter (QObject *obj, QEvent *evt);

protected slots:
    void loadProgress(int);
    void loadFinished(bool);
    void urlChanged(QUrl);
    void titleChanged(QString);
    void linkClicked(QUrl);
    void scrollPositionChanged(uint x, uint y);
    void contentSizeChanged(const QSize&);
    void onSelectIndexes(QList<int>);
    void inputText (QString input);

private:
    QGraphicsWebView m_webview;
    InputHandler m_inputHandler;
    int m_currentProgress;
    uint m_scrollPositionX;
    uint m_scrollPositionY;
    cachemanager *m_cacheManager;
};


#endif /* BROWSERVIEW_H */
