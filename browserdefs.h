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

#ifndef BROWSERDEFS_H
#define BROWSERDEFS_H

#include <QDBusArgument>

namespace conn {
    namespace brw {

    /*!
        * Browser errors definition.

        EID_NO_ERROR - No error
        EID_ALREADY_EXIST - Object already exists. It does not mean always an error. The browser could return EID_ALREADY_EXIST as info and provides required access data.
        EID_NOT_EXISTS - Object not exists. By the delete operation this error code is treated as a info status.
        EID_GENERAL_ERROR - Situation in which programmer did not know what to do
        EID_NOT_IMPLEMENTED - Method, functionality not implemented
        EID_NULL_POINTER - Null pointer
        EID_INVALID_STATE - The system or component is not ready execute the requested operation.
        EID_MAX_NUMBER_REACHED - Maximum number of records is reached.
        EID_INVALID_ARGUMENT - Invalid argument
        EID_DB_ITEM_NOT_EXISTS - Item does not exists in database
        EID_DB_ITEM_ALREADY_EXISTS - Item already exists in database
        EID_DB_CLOSED_HANDLE - Handle to database is closed
        EID_DB_QUERY_FAILS - Prepare of query fails
        EID_DB_EXEC_FAILS - Execute of query on database fails
        EID_DB_FILE_EXISTS - DB cannot create file on drive because file already exists
        EID_DB_DISK_OUT_OF_SPACE - DB cannot create file on drive because there is not enough space
        EID_DB_NO_PERMISSION - DB cannot write to file - lack of permission
        */
    //## type ERROR_IDS
    enum ERROR_IDS {
        EID_NO_ERROR,
        EID_ALREADY_EXIST,
        EID_GENERAL_ERROR,
        EID_NOT_IMPLEMENTED,
        EID_NULL_POINTER,
        EID_INVALID_STATE,
        EID_MAX_NUMBER_REACHED,
        EID_INVALID_ARGUMENT,
        EID_NOT_EXISTS,
        EID_DB_ITEM_NOT_EXISTS,
        EID_DB_ITEM_ALREADY_EXISTS,
        EID_DB_CLOSED_HANDLE,
        EID_DB_QUERY_FAILS,
        EID_DB_EXEC_FAILS,
        EID_DB_FILE_EXISTS,
        EID_DB_DISK_OUT_OF_SPACE,
        EID_DB_NO_PERMISSION,
        EID_FILESYSTEM_ERROR // TODO added
    };

    inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::ERROR_IDS &errorid)
    {
        qDebug() << __PRETTY_FUNCTION__;
        int i;
        argument.beginStructure();
        argument >> i;
        errorid = static_cast<conn::brw::ERROR_IDS>(i);
        argument.endStructure();
        return argument;
    }

    inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::ERROR_IDS &errorid)
    {
        qDebug() << __PRETTY_FUNCTION__;
        argument.beginStructure();
        argument << static_cast<int>(errorid);
        argument.endStructure();
        return argument;
    }

    
    /*!
        * Defines sorting order of bookmarks:
        BST_UNSORTED - the bookmarks item are provided in the order how they have been added by the user.
        BST_TITLE_ASCENDING - the bookmarks are sorted by the title in ascending order;
        BST_TITLE_DESCENDING - the bookmarks are sorted by the title in descending order;
        BST_URL_ASCENDING - the bookmarks are sorted by the url in ascending order;
        BST_URL_DESCENDING - the bookmarks are sorted by the url in descending order;
        */
        //## type BOOKMARK_SORT_TYPE
        enum BOOKMARK_SORT_TYPE {
            BST_UNSORTED = 0,
            BST_TITLE_ASCENDING = 1,
            BST_TITLE_DESCENDING = 2,
            BST_URL_ASCENDING = 3,
            BST_URL_DESCENDING = 4
        };
    
        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::BOOKMARK_SORT_TYPE &bookmarksorttype)
        {
            qDebug() << __PRETTY_FUNCTION__;
            int i;
            argument.beginStructure();
            argument >> i;
            bookmarksorttype = static_cast<conn::brw::BOOKMARK_SORT_TYPE>(i);
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::BOOKMARK_SORT_TYPE &bookmarksorttype)
        {
            qDebug() << __PRETTY_FUNCTION__;
            argument.beginStructure();
            argument << static_cast<int>(bookmarksorttype);
            argument.endStructure();
            return argument;
        }

        /*!
                *
                */
        //## type BookmarkItem
        struct BookmarkItem {
            /*!
                    *
                    */
            int i32Uid;		//## attribute i32Uid
            /*!
                    *
                    */
            int i32Type;		//## attribute eType
            /*!
                    *
                    */
            QString strParentFolderPath;		//## attribute strParentFolderPath
            /*!
                    *
                    */
            QString strTitle;		//## attribute strTitle
            /*!
                    *
                    */
            QString strUrl;		//## attribute strUrl
            /*!
                    *
                    */
            QString strIconPath;		//## attribute strIconPath
            /*!
                    *
                    */
            QString strThumbnailPath;		//## attribute strThumbnailPath

            BookmarkItem()
                : i32Uid(0)
                , i32Type(0)
                , strParentFolderPath("")
                , strTitle("")
                , strUrl("")
                , strIconPath("")
                , strThumbnailPath("")
            {}
        };

        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::BookmarkItem &bookmarkitem)
        {
            qDebug() << __PRETTY_FUNCTION__;
            argument.beginStructure();
            argument >> bookmarkitem.i32Uid >> bookmarkitem.i32Type >> bookmarkitem.strParentFolderPath >>
                        bookmarkitem.strTitle >> bookmarkitem.strUrl >> bookmarkitem.strIconPath >> bookmarkitem.strThumbnailPath;
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::BookmarkItem &bookmarkitem)
        {
            qDebug() << __PRETTY_FUNCTION__;
            argument.beginStructure();
            argument << bookmarkitem.i32Uid << bookmarkitem.i32Type << bookmarkitem.strParentFolderPath <<
                        bookmarkitem.strTitle << bookmarkitem.strUrl << bookmarkitem.strIconPath << bookmarkitem.strThumbnailPath;
            argument.endStructure();
            return argument;
        }

    }
}

Q_DECLARE_METATYPE(conn::brw::ERROR_IDS)
Q_DECLARE_METATYPE(conn::brw::BOOKMARK_SORT_TYPE)
Q_DECLARE_METATYPE(conn::brw::BookmarkItem)

#endif // BROWSERDEFS_H
