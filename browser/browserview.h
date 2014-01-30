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

#include "../common/browserdefs.h"


class InputHandler : public QObject {
Q_OBJECT
public slots:
    void setScrollPosition (const int &x, const int &y) {
        emit onScroll ((uint)x,(uint)y);
    }
    void setCurrentFocus (const QWebElement &elem) {
    emit onInputText (elem.attribute("name"), elem.attribute("value"),
                      elem.attribute("type", "0").toInt(),
                      elem.attribute("maxlength", "0").toInt(),
                      elem.attribute("max", "0").toInt(),
                      elem.attribute("min","0").toInt(),
                      elem.attribute("step","0").toInt());
    }
    const QWebElement *currentFocus () { return m_elem; }

signals:
    void onInputText(QString name, QString value, int type, int maxlength,
                     int max, int min, int step);
    void onScroll(uint x, uint y);

private:
    QWebElement *m_elem;
};

class BrowserView : public QGraphicsView
{
     Q_OBJECT
public:
    BrowserView();
    bool load(const QString &a_Url);
    int getProgress() { return m_currentProgress; }
    QString getUrl() { return m_webview.url().toString(); }
    const QString getTitle() { return m_webview.title(); }
    void goBack() { m_webview.back(); }
    void goForward() { m_webview.forward(); }
    void pageReload() { m_webview.reload(); }
    void pageStop() { m_webview.stop(); }
    void scroll (conn::brw::SCROLL_DIRECTION dir, conn::brw::SCROLL_TYPE type);
    void inputText (QString input);
    QSize contentSize();
    void setZoomFactor(double);
    double getZoomFactor();

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

protected:
    virtual void resizeEvent (QResizeEvent *event);
    virtual bool eventFilter (QObject *obj, QEvent *evt);

protected slots:
    void loadProgress(int);
    void loadFinished(bool);
    void urlChanged(QUrl);
    void titleChanged(QString);
    void linkClicked(QUrl);

private:
    QGraphicsWebView m_webview;
    InputHandler m_inputHandler;
    int m_currentProgress;
};


#endif /* BROWSERVIEW_H */
