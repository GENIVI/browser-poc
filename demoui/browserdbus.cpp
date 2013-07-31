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

#include "browserdbus.h"

#include "../common/browserdefs.h"

#include <QDBusMetaType>
#include <QtQml>


#define NUMBER_OF_BOOKMARKS 20

browserdbus::browserdbus(QObject *parent) :
    QObject(parent)
{
    qmlRegisterType<browserdbus>("browserdbusinterface",1,0,"BrowserInterface");
    qmlRegisterType<Bookmark>("browserdbusinterface",1,0,"Tmp");

    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::BookmarkItem>();
    qDBusRegisterMetaType<conn::brw::BookmarkItemList>();

    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();

    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();

    bookmark = new conn::brw::IBookmarkManager("conn.brw.IBookmarkManager", "/bookmarkmanager",
                                               QDBusConnection::sessionBus(), this);

    userinput = new conn::brw::IUserInput("conn.brw.IUserInput", "/userinput",
                                          QDBusConnection::sessionBus(), this);

    webpagewindow = new conn::brw::IWebPageWindow("conn.brw.IWebPageWindow", "/webpagewindow",
                                                  QDBusConnection::sessionBus(), this);

    browser = new conn::brw::IBrowser("conn.brw.IBrowser", "/browser",
                                      QDBusConnection::sessionBus(), this);
}


void browserdbus::goBack() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = webpagewindow->back();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::goForward() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = webpagewindow->forward();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::reload() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = webpagewindow->reload();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::loadurl(QString url) {
    qDebug() << __PRETTY_FUNCTION__ << url;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = webpagewindow->load(url);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}


void browserdbus::addBookmark(QString bookmarkurl, QString bookmarktitle) {
    qDebug() << __PRETTY_FUNCTION__ << bookmarkurl << bookmarktitle;

    conn::brw::BookmarkItem test;

    test.i32Uid = 0;
    test.i32Type = 1;
    test.strParentFolderPath = "";
    test.strTitle = bookmarktitle;
    test.strUrl = bookmarkurl;
    test.strIconPath = "";
    test.strThumbnailPath = "";

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->addItem(test);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::getBookmarks() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::BookmarkItemList> reply = bookmark->getItems("", 1, conn::brw::BST_UNSORTED, 1, NUMBER_OF_BOOKMARKS);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::BookmarkItemList bookmarklist = reply.argumentAt<1>();

        m_bookmarkList.clear();

        for (int i = 0; i < bookmarklist.size(); ++i) {
            qDebug() << "BookmarkItemList " << bookmarklist.at(i).i32Uid << bookmarklist.at(i).strTitle << bookmarklist.at(i).strUrl << bookmarklist.at(i).strParentFolderPath;

            m_bookmarkList.append(new Bookmark(bookmarklist.at(i).strTitle, bookmarklist.at(i).strUrl));
            emit bookmarkListChanged();
        }
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}


void browserdbus::deleteAllBookmarks() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteAllItems(1);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        m_bookmarkList.clear();
        emit bookmarkListChanged();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::getCurrentUrlAndTitle() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, QString, QString> reply = webpagewindow->getCurrentUrlTitle();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        setUrl(reply.argumentAt<1>());
        setTitle(reply.argumentAt<2>());
        }
}
