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

#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include <QObject>

#include "../browserdefs.h"
#include "bookmark.h"


class bookmarkmanager : public QObject
{
    Q_OBJECT

public:
    explicit bookmarkmanager(QObject *parent = 0);

signals:
    
public Q_SLOTS:
    conn::brw::ERROR_IDS addItem(const conn::brw::BookmarkItem & a_oItem);
    conn::brw::ERROR_IDS deleteAllItems(int a_i32BookmarkItemType);
    conn::brw::ERROR_IDS deleteItem(int a_i32Uid);
//    conn::brw::ERROR_IDS getItems(const QString &a_strParentFolderPath, int a_i32BookmarkType,
//                                  conn::brw::BOOKMARK_SORT_TYPE a_eSortingOrder, uint a_u32StartIndex, uint a_u32ItemsCount);
    conn::brw::BookmarkItemList getItems(const QString &a_strParentFolderPath, int a_i32BookmarkType,
                                  conn::brw::BOOKMARK_SORT_TYPE a_eSortingOrder, uint a_u32StartIndex, uint a_u32ItemsCount);
private:
    QList<Bookmark*> bookmarklist;

    void printbookmarklist();
};

#endif // BOOKMARKMANAGER_H
