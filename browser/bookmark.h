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

#include <QDateTime>

class Bookmark : public QObject
{
    Q_OBJECT
public:
    explicit Bookmark(QObject *parent = 0);
    
    void setUid(int uid) { i32Uid = uid; }
    void setType(int type) { i32Type = type; }
    void setParentFolderPath(QString folderpath) { strParentFolderPath = folderpath; }
    void setTitle(QString title) { strTitle = title; }
    void setUrl(QString url) { strUrl = url; }
    void setIconPath(QString iconpath) { strIconPath = iconpath; }
    void setThumbnailPath(QString thumbnailpath) { strThumbnailPath = thumbnailpath; }

    int uid() { return i32Uid; }
    int type() { return i32Type; }
    QString folderpath() { return strParentFolderPath; }
    QString title() { return strTitle; }
    QString url() { return strUrl; }
    QString iconpath() { return strIconPath; }
    QString thumbnailpath() { return strThumbnailPath; }

signals:
    
public slots:
    
private:
    int     i32Uid;
    int     i32Type;
    QString strParentFolderPath;
    QString strTitle;
    QString strUrl;
    QString strIconPath;
    QString strThumbnailPath;
};

class ApplicationData : public QObject
 {
     Q_OBJECT
 public:
     Q_INVOKABLE QDateTime getCurrentDateTime() const {
         return QDateTime::currentDateTime();
     }
 };

#endif // BOOKMARK_H
