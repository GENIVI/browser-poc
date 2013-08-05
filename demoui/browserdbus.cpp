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

#include <QDBusMetaType>
#include <QtQml>

#include "browserdbus.h"

#include "../common/browserdefs.h"


#define NUMBER_OF_BOOKMARKS 20

BrowserDbus::BrowserDbus(QObject *parent) :
    QObject(parent)
{
    qmlRegisterType<BrowserDbus>("browserdbusinterface",1,0,"BrowserInterface");
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





    connect(webpagewindow, SIGNAL(onLoadStarted(QString)),this,SLOT(testSlot(QString)));
}


void BrowserDbus::testSlot(QString url) {
    qDebug() << __PRETTY_FUNCTION__ << url;

    setUrl(url);
    emit urlChanged();
}


void BrowserDbus::goBack() {
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

void BrowserDbus::goForward() {
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

void BrowserDbus::reload() {
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

void BrowserDbus::loadurl(QString url) {
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

void BrowserDbus::addBookmark(QString bookmarkurl, QString bookmarktitle) {
    qDebug() << __PRETTY_FUNCTION__ << bookmarkurl << bookmarktitle;

    conn::brw::BookmarkItem tmpbookmark;
    tmpbookmark.i32Uid = 0;
    tmpbookmark.i32Type = 1;
    tmpbookmark.strParentFolderPath = "";
    tmpbookmark.strTitle = bookmarktitle;
    tmpbookmark.strUrl = bookmarkurl;
    tmpbookmark.strIconPath = "";
    tmpbookmark.strThumbnailPath = "";

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->addItem(tmpbookmark);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::getBookmarks() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::BookmarkItemList> reply = bookmark->getItems("", 1, conn::brw::BST_UNSORTED, 1, NUMBER_OF_BOOKMARKS);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::BookmarkItemList bookmarklist = reply.argumentAt<1>();

        m_bookmarkList.clear();
        for (int i = 0; i < bookmarklist.size(); ++i) {
            qDebug() << "BookmarkItemList " << bookmarklist.at(i).i32Uid << bookmarklist.at(i).strTitle << bookmarklist.at(i).strUrl << bookmarklist.at(i).strParentFolderPath;
            m_bookmarkList.append(new Bookmark(bookmarklist.at(i).strTitle, bookmarklist.at(i).strUrl, bookmarklist.at(i).i32Uid));
            emit bookmarkListChanged();
        }
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::deleteAllBookmarks() {
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

void BrowserDbus::deleteBookmark(int index) {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteItem(m_bookmarkList.at(index)->uid());
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }

    m_bookmarkList.removeAt(index);
    emit bookmarkListChanged();
}

void BrowserDbus::getCurrentUrlAndTitle() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, QString, QString> reply = webpagewindow->getCurrentUrlTitle();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        setUrl(reply.argumentAt<1>());
        setTitle(reply.argumentAt<2>());
    }
}