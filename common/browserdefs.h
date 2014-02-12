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
        int i;
        argument.beginStructure();
        argument >> i;
        errorid = static_cast<conn::brw::ERROR_IDS>(i);
        argument.endStructure();
        return argument;
    }

    inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::ERROR_IDS &errorid)
    {
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
            int i;
            argument.beginStructure();
            argument >> i;
            bookmarksorttype = static_cast<conn::brw::BOOKMARK_SORT_TYPE>(i);
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::BOOKMARK_SORT_TYPE &bookmarksorttype)
        {
            argument.beginStructure();
            argument << static_cast<int>(bookmarksorttype);
            argument.endStructure();
            return argument;
        }


        //## type BookmarkItem
        struct BookmarkItem {
            int i32Uid;                     //## attribute i32Uid
            int i32Type;                    //## attribute eType
            QString strParentFolderPath;    //## attribute strParentFolderPath
            QString strTitle;               //## attribute strTitle
            QString strUrl;                 //## attribute strUrl
            QString strIconPath;            //## attribute strIconPath
            QString strThumbnailPath;       //## attribute strThumbnailPath

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
            argument.beginStructure();
            argument >> bookmarkitem.i32Uid >> bookmarkitem.i32Type >> bookmarkitem.strParentFolderPath >>
                        bookmarkitem.strTitle >> bookmarkitem.strUrl >> bookmarkitem.strIconPath >> bookmarkitem.strThumbnailPath;
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::BookmarkItem &bookmarkitem)
        {
            argument.beginStructure();
            argument << bookmarkitem.i32Uid << bookmarkitem.i32Type << bookmarkitem.strParentFolderPath <<
                        bookmarkitem.strTitle << bookmarkitem.strUrl << bookmarkitem.strIconPath << bookmarkitem.strThumbnailPath;
            argument.endStructure();
            return argument;
        }


        
        //## class BookmarkItemList
        typedef QList<conn::brw::BookmarkItem> BookmarkItemList;    
        
        /*!
        * 
        */
        //## type SelectableOption
        struct SelectableOption {
            /*!
             * True - option can be selected; False - not - probably optgroup
             */
            bool bIsSelectableOption;
            /*!
            * 
            */
            QString strValue;		//## attribute strValue
            /*!
            * 
            */
            bool bSelected;		//## attribute bSelected

            SelectableOption() : bIsSelectableOption(true), strValue(), bSelected(false) {}
        };
        
        //## package connImports::Interfaces::conn::brw::def
        
        //## class SelectableOptionList
        /*!
        * 
        */
        typedef QList<conn::brw::SelectableOption> SelectableOptionList;

        //## operation operator>>(QDBusArgument,SelectableOption)
        inline const QDBusArgument& operator>>(const QDBusArgument& args, SelectableOption& selectableOption) {
            //#[ operation operator>>(QDBusArgument,SelectableOption)

            args.beginStructure();

            args >> selectableOption.bIsSelectableOption
                 >> selectableOption.strValue
                 >> selectableOption.bSelected;

            args.endStructure();
            return args;

            //#]
        }


        //## operation operator<<(QDBusArgument,SelectableOption)
        inline QDBusArgument& operator<<(QDBusArgument& args, const SelectableOption& selectableOption) {
            //#[ operation operator<<(QDBusArgument,SelectableOption)

            args.beginStructure();

            args << selectableOption.bIsSelectableOption
                 << selectableOption.strValue
                 << selectableOption.bSelected;

            args.endStructure();

            return args;

            //#]
        }
        

        /*!
                * Result of dialog.
                DR_OK - Prompt is accepted
                DR_CANCEL - Prompt is canceled
                */
        //## type DIALOG_RESULT
        enum DIALOG_RESULT {
            DR_OK,
            DR_CANCEL
        };

        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::DIALOG_RESULT &dialogresult)
        {
            int i;
            argument.beginStructure();
            argument >> i;
            dialogresult = static_cast<conn::brw::DIALOG_RESULT>(i);
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::DIALOG_RESULT &dialogresult)
        {
            argument.beginStructure();
            argument << static_cast<int>(dialogresult);
            argument.endStructure();
            return argument;
        }

        /*!
                * Types of input element. See HTML5.

                IET_TEXT - The text input type defines a one-line input field that a user can enter text into.
                IET_COLOR - The color input type is used to specify a color.
                IET_DATE - The date input type is used to specify data, month and year
                IET_MONTH - The month input type is used to specify month and year
                IET_WEEK - The week input type is used to specify a week and year
                IET_TIME - The time input type is used to specify a time(hour and minute)
                IET_DATETIME - The datetime  input type is used to specify time, date, month and year (UTC time)
                IET_DATETIME_LOCAL - The datetime-local  input type is used to specify time, date, month and year (local time).
                IET_EMAIL - The email input type is used for input fields that should contain an e-mail address.
                IET_FILE - The file input type is used for file uploads.
                IET_NUMBER - The number input type is used for input fields that should contain a numeric value.
                IET_PASSWORD - The password input type defines a password field. The characters in a password field are masked (shown as asterisks or circles).
                IET_TEL - The tel input type is used for input fields that should contain a telephone number.
                IET_URL - The url input type is used for input fields that should contain a URL address.
                */
        //## type INPUT_ELEMENT_TYPE
        enum INPUT_ELEMENT_TYPE {
            IET_TEXT = 0,
            IET_COLOR = 1,
            IET_DATE = 2,
            IET_MONTH = 3,
            IET_WEEK = 4,
            IET_TIME = 5,
            IET_DATETIME = 6,
            IET_DATETIME_LOCAL = 7,
            IET_EMAIL = 8,
            IET_FILE = 9,
            IET_NUMBER = 10,
            IET_PASSWORD = 11,
            IET_TEL = 12,
            IET_URL = 13
        };

        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::INPUT_ELEMENT_TYPE &inputtype)
        {
            int i;
            argument.beginStructure();
            argument >> i;
            inputtype = static_cast<conn::brw::INPUT_ELEMENT_TYPE>(i);
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::INPUT_ELEMENT_TYPE &inputtype)
        {
            argument.beginStructure();
            argument << static_cast<int>(inputtype);
            argument.endStructure();
            return argument;
        }



        /*!
                * Direction of scrolling or link selection.
                */
        //## type SCROLL_DIRECTION
        enum SCROLL_DIRECTION {
            SD_LEFT,
            SD_RIGHT,
            SD_TOP,
            SD_BOTTOM
        };

        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::SCROLL_DIRECTION &scrolldirection)
        {
            int i;
            argument.beginStructure();
            argument >> i;
            scrolldirection = static_cast<conn::brw::SCROLL_DIRECTION>(i);
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::SCROLL_DIRECTION &scrolldirection)
        {
            argument.beginStructure();
            argument << static_cast<int>(scrolldirection);
            argument.endStructure();
            return argument;
        }

        /*!
                * Type of scrolling.
                ST_SYMBOL - Scrolling line by line.
                ST_PAGE - Scroll to the next or previous page.
                ST_LINK - Jump to the link.
                */
        //## type SCROLL_TYPE
        enum SCROLL_TYPE {
            ST_SYMBOL = 0,
            ST_PAGE = 1,
            ST_LINK = 2
        };

        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::SCROLL_TYPE &scrolltype)
        {
            int i;
            argument.beginStructure();
            argument >> i;
            scrolltype = static_cast<conn::brw::SCROLL_TYPE>(i);
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::SCROLL_TYPE &scrolltype)
        {
            argument.beginStructure();
            argument << static_cast<int>(scrolltype);
            argument.endStructure();
            return argument;
        }

              
        //## type Rect
        struct Rect {
            int i32X;		//## attribute i32X
            int i32Y;		//## attribute i32Y
            int i32Width;	//## attribute i32Width
            int i32Height;	//## attribute i32Height

            Rect() : i32X(0), i32Y(0), i32Width(0), i32Height(0) {}
        };

        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::Rect &rect)
        {
            argument.beginStructure();
            argument >> rect.i32X >> rect.i32Y >> rect.i32Width >>
                        rect.i32Height;
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::Rect &rect)
        {
            argument.beginStructure();
            argument << rect.i32X << rect.i32Y << rect.i32Width <<
                        rect.i32Height;
            argument.endStructure();
            return argument;
        }



        /*!
        * Defines type of the object handlers.
        */
        //## type OBJECT_HANDLE
        typedef qlonglong OBJECT_HANDLE;
        
        //## class ObjectHandleList
        typedef QList<conn::brw::OBJECT_HANDLE> ObjectHandleList;
        
        
        /*!
        * Browser scroll directions structure.
        */
        //## type BrowserScrollDirections
        struct BrowserScrollDirections {
            uchar u8Left;       //## attribute u8Left
            uchar u8Right;      //## attribute u8Right
            uchar u8Top;        //## attribute u8Top
            uchar u8Bottom;     //## attribute u8Bottom

            BrowserScrollDirections()
                : u8Left(0)
                , u8Right(0)
                , u8Top(0)
                , u8Bottom(0)
            {}
        };
        
        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::BrowserScrollDirections &browserscrolldirection)
        {
            argument.beginStructure();
            argument >> browserscrolldirection.u8Left >> browserscrolldirection.u8Right >> browserscrolldirection.u8Top >>
                        browserscrolldirection.u8Bottom;
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::BrowserScrollDirections &browserscrolldirection)
        {
            argument.beginStructure();
            argument << browserscrolldirection.u8Left << browserscrolldirection.u8Right << browserscrolldirection.u8Top <<
                        browserscrolldirection.u8Bottom;
            argument.endStructure();
            return argument;
        }



        /*!
        * Structure describes availability of the actions in the browser. For example, if the BrowserActions::u8Back=0x03, the HMI could highlight the "back" button, if the state is 0x00 the "back" action is not available, HMI could show the "back" button in the disabled state.
        */
        //## type BrowserActions
        struct BrowserActions {
            /*!
            * Defines state of IPageView::back method/button.
            */
            uchar u8Back;       //## attribute u8Back
            /*!
            * Defines state of IPageView::forward method/button.
            */
            uchar u8Forward;        //## attribute u8Forward
            /*!
            * Defines state of IPageView::reload method/button.
            */
            uchar u8Reload;     //## attribute u8Reload
            /*!
            * Defines state of IPageView::stop method/button.
            */
            uchar u8Stop;       //## attribute u8Stop
            /*!
            * Defines state of IPageView::loadUrl method/button.
            */
            uchar u8LoadUrl;        //## attribute u8LoadUrl
            /*!
            * Defines state of IPageView::select method/button.
            */
            uchar u8Select;     //## attribute u8Select
            /*!
            * Defines state of IPageView::scroll(*, ST_SYMBOL) method/button.
            */
            BrowserScrollDirections sScrollSymbol;      //## attribute sScrollSymbol
            /*!
            * Defines state of IPageView::scroll(*, ST_PAGE) method/button.
            */
            BrowserScrollDirections sScrollPage;        //## attribute sScrollPage
            /*!
            * Defines state of IPageView::scroll(*, ST_LINK) method/button.
            */
            BrowserScrollDirections sScrollLink;        //## attribute sScrollLink

            BrowserActions()
            : u8Back(0)
            , u8Forward(0)
            , u8Reload(0)
            , u8Stop(0)
            , u8LoadUrl(0)
            , u8Select(0)
            , sScrollSymbol()
            , sScrollPage()
            , sScrollLink()
            {}
        };

        inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::BrowserActions &browseractions)
        {
            argument.beginStructure();
            argument >> browseractions.u8Back >> browseractions.u8Forward >> browseractions.u8Reload >>
                        browseractions.u8Stop >> browseractions.u8LoadUrl >> browseractions.u8Select >>
                        browseractions.sScrollSymbol >> browseractions.sScrollPage >> browseractions.sScrollLink;
            argument.endStructure();
            return argument;
        }

        inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::BrowserActions &browseractions)
        {
            argument.beginStructure();
            argument << browseractions.u8Back << browseractions.u8Forward << browseractions.u8Reload <<
                        browseractions.u8Stop << browseractions.u8LoadUrl << browseractions.u8Select <<
                        browseractions.sScrollSymbol << browseractions.sScrollPage << browseractions.sScrollLink;
            argument.endStructure();
            return argument;
        }
        
        /*!
        * Defines policy of cache usage.
        CP_CACHE_ONLINE - Use cache if present, network if not.
        CP_CACHE_ONLY - Only cache is used.
        CP_ONLINE_ONLY - Cache is disabled.
        
        */
        //## type CACHE_POLICY
        enum CACHE_POLICY {
            CP_ONLINE_CACHE = 0x00,
            CP_CACHE_ONLY = 0x01,
            CP_ONLINE_ONLY = 0x02
        };

        //## operation operator>>(QDBusArgument,CACHE_POLICY)
        inline const QDBusArgument& operator>>(const QDBusArgument& args, CACHE_POLICY& cachePolicy) {
            //#[ operation operator>>(QDBusArgument,CACHE_POLICY)
            args.beginStructure();
            int temp =0;
            args>>temp;
            switch (temp )
            {
            case CP_ONLINE_CACHE:
            {
                cachePolicy = CP_ONLINE_CACHE;
            }
                break;
            case CP_CACHE_ONLY :
            {
                cachePolicy = CP_CACHE_ONLY;
            }
                break;
            case CP_ONLINE_ONLY:
            {
                cachePolicy = CP_ONLINE_ONLY;
            }
                break;
            }

            args.endStructure();
            return args;
            //#]
        }

        //## operation operator<<(QDBusArgument,CACHE_POLICY)
        inline const QDBusArgument& operator<<(QDBusArgument& args, CACHE_POLICY cachePolicy) {
            //#[ operation operator<<(QDBusArgument,CACHE_POLICY)
            args.beginStructure();
            int param = cachePolicy;
            args << param;
            args.endStructure();
            return args;
            //#]
        }

        /*!
        * Defines sorting order of error items:
        EST_DATE_ASCENDING - the error items are sorted by the date in ascending order;
        EST_DATE_DESCENDING - the error items are sorted by the date in descending order;

        */
        //## type ERROR_SORT_TYPE
        enum ERROR_SORT_TYPE
        {
            EST_DATE_ASCENDING = 0,
            EST_DATE_DESCENDING = 1
        };

        struct ErrorItem
        {
            /*!
            * Timestamp when the error happened
            */
            qlonglong i64DateTime;		//## attribute i64DateTime
            /*!
            * Browser version
            */
            QString strBrowserVersion;		//## attribute strBrowserVersion
            /*!
            * Internet connection used.
            */
            QString strConnectionType;		//## attribute strConnectionType
            /*!
            * Error code. It could be HTTP error codes, or internal codes.
            */
            QString strCode;		//## attribute strCode
            /*!
            * Information about the place where the error happened. Could be name of a module, class or method.
            */
            QString strSource;		//## attribute strSource
            /*!
            * Short text description of the error.
            */
            QString strDescription;		//## attribute strDescription
        };

        //## package connInterfaces::connPublic::conn::brw::def
        //## class ErrorItemList
        /*!
        *
        */
        typedef QList<conn::brw::ErrorItem> ErrorItemList;

        //## operation operator>>(QDBusArgument,ErrorItem)
        inline const QDBusArgument& operator>>(const QDBusArgument& args, ErrorItem& error) {
            //#[ operation operator>>(QDBusArgument,ErrorItem)
            args.beginStructure();
            args >> error.i64DateTime
                 >> error.strBrowserVersion
                 >> error.strConnectionType
                 >> error.strCode
                 >> error.strSource
                 >> error.strDescription;
            args.endStructure();
            return args;
            //#]
        }

        //## operation operator<<(QDBusArgument,ErrorItem)
        inline QDBusArgument& operator<<(QDBusArgument& args, const ErrorItem& error) {
            //#[ operation operator<<(QDBusArgument,ErrorItem)
            args.beginStructure();
            args << error.i64DateTime
                 << error.strBrowserVersion
                 << error.strConnectionType
                 << error.strCode
                 << error.strSource
                 << error.strDescription;
            args.endStructure();
            return args;
            //#]
        }
    }
}

Q_DECLARE_METATYPE(conn::brw::ERROR_IDS)
Q_DECLARE_METATYPE(conn::brw::BOOKMARK_SORT_TYPE)
Q_DECLARE_METATYPE(conn::brw::BookmarkItem)
Q_DECLARE_METATYPE(conn::brw::BookmarkItemList)
Q_DECLARE_METATYPE(conn::brw::DIALOG_RESULT)
Q_DECLARE_METATYPE(conn::brw::INPUT_ELEMENT_TYPE)
Q_DECLARE_METATYPE(conn::brw::SCROLL_DIRECTION)
Q_DECLARE_METATYPE(conn::brw::SCROLL_TYPE)
Q_DECLARE_METATYPE(conn::brw::Rect)
Q_DECLARE_METATYPE(conn::brw::BrowserScrollDirections)
Q_DECLARE_METATYPE(conn::brw::BrowserActions)
Q_DECLARE_METATYPE(conn::brw::OBJECT_HANDLE)
Q_DECLARE_METATYPE(conn::brw::ObjectHandleList)
Q_DECLARE_METATYPE(conn::brw::SelectableOption);
Q_DECLARE_METATYPE(conn::brw::CACHE_POLICY);
Q_DECLARE_METATYPE(conn::brw::ErrorItemList);
Q_DECLARE_METATYPE(conn::brw::ErrorItem);
Q_DECLARE_METATYPE(conn::brw::ERROR_SORT_TYPE);

#endif // BROWSERDEFS_H
