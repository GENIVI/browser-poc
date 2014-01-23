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

#include "../common/browserdefs.h"

class BrowserView : public QGraphicsView
{
     Q_OBJECT
public:
    BrowserView();
    bool load(const QString &a_Url);
    int getProgress() { return m_currentProgress; }
    QString getURL() { return m_webview.url().toString(); }
    const QString getTitle() { return m_webview.title(); }
    void goBack() { m_webview.back(); }
    void goForward() { m_webview.forward(); }
    void pageReload() { m_webview.reload(); }
    void pageStop() { m_webview.stop(); }
    void scroll (conn::brw::SCROLL_DIRECTION dir, conn::brw::SCROLL_TYPE type);
    void inputText (QString input);

signals:
    void pageLoadStarted();
    void pageLoadFinished(bool);
    void pageLoadProgress(int);

protected:
    virtual void resizeEvent (QResizeEvent *event);

protected slots:
    void loadProgress(int);

private:
     QGraphicsWebView m_webview;
     int m_currentProgress;

};

#endif /* BROWSERVIEW_H */
