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

class DataObject;

class browserdbus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString url READ url)
    Q_PROPERTY(QQmlListProperty<Bookmark> bookmarkList READ getBookmarkList NOTIFY bookmarkListChanged)

public:
    explicit browserdbus(QObject *parent = 0);
    
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void goForward();
    Q_INVOKABLE void reload();
    Q_INVOKABLE void loadurl(QString url);
    Q_INVOKABLE void getBookmarks();
    Q_INVOKABLE void addBookmark(QString url, QString title);
    Q_INVOKABLE void getCurrentUrlAndTitle();

    QString title() { return m_title; }
    void setTitle(QString title) { m_title = title; }

    QString url() const { return m_url; }
    void setUrl(const QString &url)  { m_url = url; }

    QQmlListProperty<Bookmark> getBookmarkList() { return QQmlListProperty<Bookmark>(this, m_bookmarkList); }

signals:
    void bookmarkListChanged();

public slots:

private:
    conn::brw::IBookmarkManager *bookmark;
    conn::brw::IUserInput *userinput;
    conn::brw::IWebPageWindow *webpagewindow;
    conn::brw::IBrowser *browser;

    QString m_title;
    QString m_url;
    QList<Bookmark*> m_bookmarkList;
};


#endif // BROWSERDBUS_H
