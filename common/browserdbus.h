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
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

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
    Q_INVOKABLE void goRight(conn::brw::SCROLL_TYPE type);
    Q_INVOKABLE void goLeft(conn::brw::SCROLL_TYPE type);
    Q_INVOKABLE void goUp(conn::brw::SCROLL_TYPE type);
    Q_INVOKABLE void goDown(conn::brw::SCROLL_TYPE type);
    Q_INVOKABLE void setVisible(bool visible);
    Q_INVOKABLE void getVisible();
    Q_INVOKABLE void getGeometry();
    Q_INVOKABLE void setGeometry(int x, int y, int width, int height);
    Q_INVOKABLE void getContentSize();
    Q_INVOKABLE void getBrowserActionState();
    Q_INVOKABLE void createPageWindow(int deviceid, int x, int y, int width, int height);
    Q_INVOKABLE void destroyPageWindow(qlonglong windowhandle);
    Q_INVOKABLE void getPageWindows();
    Q_INVOKABLE void inputText(conn::brw::DIALOG_RESULT a_eResult, QString a_strInputValue);
    Q_INVOKABLE void connectdbussession(QString id);
    Q_INVOKABLE void selectTab(int tabnumber);
    Q_INVOKABLE QString getUrl();
    Q_INVOKABLE QString getTitle();

    QString title() { return m_title; }
    void setTitle(QString title) { m_title = title; }
    QString url() const { return m_url; }
    void setUrl(const QString &url)  { m_url = url; }
    bool pageloading() { return m_pageloading; }
    void setPageLoading(bool loading) { m_pageloading = loading; }
    int progress() { return m_progress; }
    void setProgress(int prog) { m_progress = prog; }
    bool connected() { return m_isconnected; }
    QQmlListProperty<Bookmark> getBookmarkList() { return QQmlListProperty<Bookmark>(this, m_bookmarkList); }

signals:
    void bookmarkListChanged();
    void urlChanged();
    void titleChanged();
    void pageloadingChanged();
    void progressChanged();
    void connectedChanged();

public slots:
    void pageloadingstarted();
    void pageloadingfinished(bool success);
    void pageloadingprogress(int progress);
    void PageWindowDestroyed(qlonglong handle);
    void PageWindowCreated(qlonglong handle, conn::brw::ERROR_IDS result);
    void WindowClosed();
    void InputTextReceived(QString a_strInputName, QString a_strDefaultInputValue, conn::brw::INPUT_ELEMENT_TYPE a_i32InputValueType, int a_s32MaxLength, int a_s32Max, int a_s32Min, int a_s32Step);

private:
    conn::brw::IBookmarkManager *bookmark;
    conn::brw::IUserInput *userinput;
    conn::brw::IWebPageWindow *webpagewindow;
    conn::brw::IWebPageWindow *actualtab;
    conn::brw::IUserInput *actualuserinput;
    QList<conn::brw::OBJECT_HANDLE> handlelist;
    conn::brw::IBrowser *browser;
    QString m_title;
    QString m_url;
    QList<Bookmark*> m_bookmarkList;
    bool m_pageloading;
    int m_progress;
    QString m_instanceId;
    bool m_isconnected;
    QString *dbusservicename;
    void scrollpage(conn::brw::SCROLL_DIRECTION direction, conn::brw::SCROLL_TYPE type);
    void registertypes();
    QHash<conn::brw::OBJECT_HANDLE, conn::brw::IWebPageWindow *> webpagehash;
    QHash<conn::brw::OBJECT_HANDLE, conn::brw::IUserInput *> inputhash;
};

#endif // BROWSERDBUS_H
