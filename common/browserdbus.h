/**
 * Copyright (C) 2013, Pelagicore
 *
 * Author: Marcel Schuette <marcel.schuette@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef BROWSERDBUS_H
#define BROWSERDBUS_H

#include <QObject>
#include <QQmlListProperty>

#include "ibookmarkmanager_interface.h"
#include "iuserinput_interface.h"
#include "iwebpagewindow_interface.h"
#include "ibrowser_interface.h"
#include "../common/bookmark.h"

class BrowserDbus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    Q_PROPERTY(QQmlListProperty<Bookmark> bookmarkList READ getBookmarkList NOTIFY bookmarkListChanged)
    Q_PROPERTY(bool pageloading READ pageloading NOTIFY pageloadingChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)

public:
    explicit BrowserDbus(QObject *parent = 0);
    
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void goForward();
    Q_INVOKABLE void reload();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void loadurl(QString url);

    Q_INVOKABLE void getBookmarks(QString folder, int type, conn::brw::BOOKMARK_SORT_TYPE sorting, int start, int count);
    Q_INVOKABLE void addBookmark(int type, QString folder, QString title, QString url, QString iconpath, QString thumbnailpath);
    Q_INVOKABLE void deleteBookmark(int uid);
    Q_INVOKABLE void deleteAllBookmarks(int type);

    Q_INVOKABLE void getCurrentUrlAndTitle();

    Q_INVOKABLE void goRight();
    Q_INVOKABLE void goLeft();
    Q_INVOKABLE void goUp();
    Q_INVOKABLE void goDown();
    Q_INVOKABLE void goDownPage();
    Q_INVOKABLE void goUpPage();

    Q_INVOKABLE void openBrowserWindow();

    Q_INVOKABLE void setVisible(bool visible);
    Q_INVOKABLE void getVisible();

    Q_INVOKABLE void getGeometry();
    Q_INVOKABLE void setGeometry(int x, int y, int width, int height);

    Q_INVOKABLE void getContentSize();

    Q_INVOKABLE void getBrowserActionState();


    QString title() { return m_title; }
    void setTitle(QString title) { m_title = title; }
    QString url() const { return m_url; }
    void setUrl(const QString &url)  { m_url = url; }
    bool pageloading() { return m_pageloading; }
    void setPageLoading(bool loading) { m_pageloading = loading; }
    int progress() { return m_progress; }
    void setProgress(int prog) { m_progress = prog; }

    QQmlListProperty<Bookmark> getBookmarkList() { return QQmlListProperty<Bookmark>(this, m_bookmarkList); }

signals:
    void bookmarkListChanged();
    void urlChanged();
    void titleChanged();
    void pageloadingChanged();
    void progressChanged();

public slots:
    void pageloadingstarted();
    void pageloadingfinished(bool success);
    void pageloadingprogress(int progress);

private:
    conn::brw::IBookmarkManager *bookmark;
    conn::brw::IUserInput *userinput;
    conn::brw::IWebPageWindow *webpagewindow;
    conn::brw::IBrowser *browser;

    QString m_title;
    QString m_url;
    QList<Bookmark*> m_bookmarkList;
    bool m_pageloading;
    int m_progress;

    void scrollpage(conn::brw::SCROLL_DIRECTION direction, conn::brw::SCROLL_TYPE type);
};

#endif // BROWSERDBUS_H
