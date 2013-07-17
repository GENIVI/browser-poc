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

#include "bookmarkmanager.h"
#include <QDebug>


bookmarkmanager::bookmarkmanager(QObject *parent) :
    QObject(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
}

conn::brw::ERROR_IDS bookmarkmanager::addItem(const conn::brw::BookmarkItem & a_oItem) {
    qDebug() << __PRETTY_FUNCTION__ << a_oItem.i32Uid << a_oItem.i32Type << a_oItem.strParentFolderPath << a_oItem.strTitle
                << a_oItem.strUrl << a_oItem.strIconPath << a_oItem.strThumbnailPath;

    // check if item is valid (url is valid)
    if(a_oItem.strUrl != "") {
        // check if max items reached
        if(bookmarklist.size() >= 50) {
            return conn::brw::EID_MAX_NUMBER_REACHED;
        }

        // check if uid already exists
        for (int i = 0; i < bookmarklist.size(); ++i) {
             if (bookmarklist.at(i)->uid() == a_oItem.i32Uid) {
                 return conn::brw::EID_ALREADY_EXIST;
             }
         }

        // add item
        Bookmark *temp_bookmark = new Bookmark();
        temp_bookmark->setUid(a_oItem.i32Uid);
        temp_bookmark->setType(a_oItem.i32Type);
        temp_bookmark->setParentFolderPath(a_oItem.strParentFolderPath);
        temp_bookmark->setTitle(a_oItem.strTitle);
        temp_bookmark->setUrl(a_oItem.strUrl);
        temp_bookmark->setIconPath(a_oItem.strIconPath);
        temp_bookmark->setThumbnailPath(a_oItem.strThumbnailPath);

        bookmarklist.append(temp_bookmark);

        return conn::brw::EID_NO_ERROR;
    }
    return conn::brw::EID_INVALID_ARGUMENT;
}

conn::brw::ERROR_IDS bookmarkmanager::deleteAllItems(int type) {
    qDebug() << __PRETTY_FUNCTION__;

    bool success = false;

    // find bookmarks for type and delete
    for (int i = 0; i < bookmarklist.size(); ++i) {
        if (bookmarklist.at(i)->type() == type) {
            bookmarklist.removeAt(i--);
            success = true;
        }
    }
    return success ? conn::brw::EID_NO_ERROR : conn::brw::EID_NOT_EXISTS;
}

conn::brw::ERROR_IDS bookmarkmanager::deleteItem(int uid) {
    qDebug() << __PRETTY_FUNCTION__ << uid;

    // find bookmark for uid
    for (int i = 0; i < bookmarklist.size(); ++i) {
        if (bookmarklist.at(i)->uid() == uid) {
            bookmarklist.removeAt(i);

            return conn::brw::EID_NO_ERROR;
        }
    }
    return conn::brw::EID_NOT_EXISTS;
}

conn::brw::ERROR_IDS bookmarkmanager::getItems(const QString &path, int type, conn::brw::BOOKMARK_SORT_TYPE a_eSortingOrder, uint index, uint count, conn::brw::BookmarkItemList &a_oItems) {
    qDebug() << __PRETTY_FUNCTION__ << path << type << a_eSortingOrder << index << count;

    // TODO: sorting
    conn::brw::BookmarkItem *test = new conn::brw::BookmarkItem();
    QList<conn::brw::BookmarkItem> bmlist;

    uint added = 0;
    uint found = 0;

    for (int i = 0; i < bookmarklist.size(); ++i) {
        if (bookmarklist.at(i)->folderpath() == path && bookmarklist.at(i)->type() == type && added < count) {

            found++;
            if(found >= index) {
                test->i32Type = bookmarklist.at(i)->type();
                test->i32Uid = bookmarklist.at(i)->uid();
                test->strIconPath = bookmarklist.at(i)->iconpath();
                test->strParentFolderPath = bookmarklist.at(i)->folderpath();
                test->strThumbnailPath = bookmarklist.at(i)->thumbnailpath();
                test->strTitle = bookmarklist.at(i)->title();
                test->strUrl = bookmarklist.at(i)->url();

                bmlist.append(*test);
                added++;
            }
        }
    }

//    return bmlist;

    return conn::brw::EID_NO_ERROR;
}

void bookmarkmanager::printbookmarklist() {
    for (int i = 0; i < bookmarklist.size(); ++i)
        qDebug() << i << bookmarklist.at(i)->url();
}
