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

#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QObject>

class Bookmark : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    Q_PROPERTY(int uid READ uid NOTIFY uidChanged)

public:
    explicit Bookmark(QObject *parent = 0);
    explicit Bookmark(QString aname, QString aurl, int uid) { strTitle = aname; strUrl = aurl; i32Uid = uid; }
    
    int uid() { return i32Uid; }
    void setUid(int uid) { i32Uid = uid; }
    int type() { return i32Type; }
    void setType(int type) { i32Type = type; }
    QString folderpath() { return strParentFolderPath; }
    void setParentFolderPath(QString folderpath) { strParentFolderPath = folderpath; }
    QString title() { return strTitle; }
    void setTitle(QString title) { strTitle = title; }
    QString url() { return strUrl; }
    void setUrl(QString url) { strUrl = url; }
    QString iconpath() { return strIconPath; }
    void setIconPath(QString iconpath) { strIconPath = iconpath; }
    QString thumbnailpath() { return strThumbnailPath; }
    void setThumbnailPath(QString thumbnailpath) { strThumbnailPath = thumbnailpath; }

signals:
    void urlChanged();
    void titleChanged();
    void uidChanged();
    
private:
    int     i32Uid;
    int     i32Type;
    QString strParentFolderPath;
    QString strTitle;
    QString strUrl;
    QString strIconPath;
    QString strThumbnailPath;
};

#endif // BOOKMARK_H
