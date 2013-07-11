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
    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS bookmarkmanager::deleteAllItems(int type) {
    qDebug() << __PRETTY_FUNCTION__ << type;
    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS bookmarkmanager::deleteItem(int uid) {
    qDebug() << __PRETTY_FUNCTION__ << uid;
    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS bookmarkmanager::getItems(const QString &path, int type, conn::brw::BOOKMARK_SORT_TYPE a_eSortingOrder, uint index, uint count) {
    qDebug() << __PRETTY_FUNCTION__ << path << type << a_eSortingOrder << index << count;
    return conn::brw::EID_NOT_IMPLEMENTED;
}
