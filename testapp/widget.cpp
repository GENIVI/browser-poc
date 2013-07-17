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

#include "widget.h"

#include <QBoxLayout>
#include <QPushButton>

#include <QDebug>

#define BUTTONHEIGHT 50


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    initializebookmarks();

    bookmark = new conn::brw::IBookmarkManager("conn.brw.IBookmarkManager", "/bookmarkmanager",
                                               QDBusConnection::sessionBus(), this);

    userinput = new conn::brw::IUserInput("conn.brw.IUserInput", "/userinput",
                                          QDBusConnection::sessionBus(), this);

    webpagewindow = new conn::brw::IWebPageWindow("conn.brw.IWebPageWindow", "/webpagewindow",
                                                  QDBusConnection::sessionBus(), this);

    browser = new conn::brw::IBrowser("conn.brw.IBrowser", "/browser",
                                      QDBusConnection::sessionBus(), this);


    QPushButton *addbookmark1 = new QPushButton("Add Bookmark1");
    addbookmark1->setFixedHeight(BUTTONHEIGHT);
    QPushButton *addbookmark2 = new QPushButton("Add Bookmark2");
    addbookmark2->setFixedHeight(BUTTONHEIGHT);
    QPushButton *addbookmark3 = new QPushButton("Add Bookmark3");
    addbookmark3->setFixedHeight(BUTTONHEIGHT);
    QPushButton *addbookmark4 = new QPushButton("Add Bookmark4");
    addbookmark4->setFixedHeight(BUTTONHEIGHT);
    QPushButton *addbookmark5 = new QPushButton("Add Bookmark5");
    addbookmark5->setFixedHeight(BUTTONHEIGHT);

    connect(addbookmark1, SIGNAL(clicked()), this, SLOT(B1addpressed()));
    connect(addbookmark2, SIGNAL(clicked()), this, SLOT(B2addpressed()));
    connect(addbookmark3, SIGNAL(clicked()), this, SLOT(B3addpressed()));
    connect(addbookmark4, SIGNAL(clicked()), this, SLOT(B4addpressed()));
    connect(addbookmark5, SIGNAL(clicked()), this, SLOT(B5addpressed()));

    QHBoxLayout *bookmarkaddbuttonlayout = new QHBoxLayout();
    bookmarkaddbuttonlayout->addWidget(addbookmark1);
    bookmarkaddbuttonlayout->addWidget(addbookmark2);
    bookmarkaddbuttonlayout->addWidget(addbookmark3);
    bookmarkaddbuttonlayout->addWidget(addbookmark4);
    bookmarkaddbuttonlayout->addWidget(addbookmark5);

    QPushButton *deletebookmark1 = new QPushButton("Delete Bookmark1");
    deletebookmark1->setFixedHeight(BUTTONHEIGHT);
    QPushButton *deletebookmark2 = new QPushButton("Delete Bookmark2");
    deletebookmark2->setFixedHeight(BUTTONHEIGHT);
    QPushButton *deletebookmark3 = new QPushButton("Delete Bookmark3");
    deletebookmark3->setFixedHeight(BUTTONHEIGHT);
    QPushButton *deletebookmark4 = new QPushButton("Delete Bookmark4");
    deletebookmark4->setFixedHeight(BUTTONHEIGHT);
    QPushButton *deletebookmark5 = new QPushButton("Delete Bookmark5");
    deletebookmark5->setFixedHeight(BUTTONHEIGHT);

    connect(deletebookmark1, SIGNAL(clicked()), this, SLOT(B1deletepressed()));
    connect(deletebookmark2, SIGNAL(clicked()), this, SLOT(B2deletepressed()));
    connect(deletebookmark3, SIGNAL(clicked()), this, SLOT(B3deletepressed()));
    connect(deletebookmark4, SIGNAL(clicked()), this, SLOT(B4deletepressed()));
    connect(deletebookmark5, SIGNAL(clicked()), this, SLOT(B5deletepressed()));

    QHBoxLayout *bookmarkdeletebuttonlayout = new QHBoxLayout();
    bookmarkdeletebuttonlayout->addWidget(deletebookmark1);
    bookmarkdeletebuttonlayout->addWidget(deletebookmark2);
    bookmarkdeletebuttonlayout->addWidget(deletebookmark3);
    bookmarkdeletebuttonlayout->addWidget(deletebookmark4);
    bookmarkdeletebuttonlayout->addWidget(deletebookmark5);

    QPushButton *deleteallbookmark1 = new QPushButton("Delete all type 0");
    deleteallbookmark1->setFixedHeight(BUTTONHEIGHT);
    QPushButton *deleteallbookmark2 = new QPushButton("Delete all type 1");
    deleteallbookmark2->setFixedHeight(BUTTONHEIGHT);
    QPushButton *deleteallbookmark3 = new QPushButton("Delete all type 2");
    deleteallbookmark3->setFixedHeight(BUTTONHEIGHT);

    connect(deleteallbookmark1, SIGNAL(clicked()), this, SLOT(B1deleteallpressed()));
    connect(deleteallbookmark2, SIGNAL(clicked()), this, SLOT(B2deleteallpressed()));
    connect(deleteallbookmark3, SIGNAL(clicked()), this, SLOT(B3deleteallpressed()));

    QHBoxLayout *bookmarkdeleteallbuttonlayout = new QHBoxLayout();
    bookmarkdeleteallbuttonlayout->addWidget(deleteallbookmark1);
    bookmarkdeleteallbuttonlayout->addWidget(deleteallbookmark2);
    bookmarkdeleteallbuttonlayout->addWidget(deleteallbookmark3);


    QPushButton *b4 = new QPushButton("Get All Bookmarks");
    b4->setFixedHeight(BUTTONHEIGHT);

    QPushButton *b5 = new QPushButton("UserInput");
    b5->setFixedHeight(BUTTONHEIGHT);
    QPushButton *b6 = new QPushButton("Reload");
    b6->setFixedHeight(BUTTONHEIGHT);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(bookmarkaddbuttonlayout);
    layout->addLayout(bookmarkdeletebuttonlayout);
    layout->addLayout(bookmarkdeleteallbuttonlayout);
    layout->addWidget(b4);
    layout->addWidget(b5);
    layout->addWidget(b6);

    connect(b4, SIGNAL(clicked()), this, SLOT(getItems()));
    connect(b5, SIGNAL(clicked()), this, SLOT(input()));
    connect(b6, SIGNAL(clicked()), this, SLOT(reload()));
}

Widget::~Widget()
{   
}

void Widget::initializebookmarks() {

    conn::brw::BookmarkItem test;

    test.i32Uid = 1;
    test.i32Type = 1;
    test.strParentFolderPath = "";
    test.strTitle = "Genivi";
    test.strUrl = "www.genivi.org";
    test.strIconPath = "";
    test.strThumbnailPath = "";

    bookmarklist.append(test);

    test.i32Uid = 2;
    test.i32Type = 1;
    test.strParentFolderPath = "";
    test.strTitle = "Google";
    test.strUrl = "www.google.com";
    test.strIconPath = "";
    test.strThumbnailPath = "";

    bookmarklist.append(test);

    test.i32Uid = 3;
    test.i32Type = 1;
    test.strParentFolderPath = "";
    test.strTitle = "Pelagicore";
    test.strUrl = "www.pelagicore.com";
    test.strIconPath = "";
    test.strThumbnailPath = "";

    bookmarklist.append(test);

    test.i32Uid = 4;
    test.i32Type = 2;
    test.strParentFolderPath = "auto";
    test.strTitle = "BMW";
    test.strUrl = "www.bmw.com";
    test.strIconPath = "";
    test.strThumbnailPath = "";

    bookmarklist.append(test);

    test.i32Uid = 5;
    test.i32Type = 2;
    test.strParentFolderPath = "auto";
    test.strTitle = "Continental";
    test.strUrl = "www.continental.com";
    test.strIconPath = "";
    test.strThumbnailPath = "";

    bookmarklist.append(test);
}

void Widget::B1addpressed() { addItem(0); }
void Widget::B2addpressed() { addItem(1); }
void Widget::B3addpressed() { addItem(2); }
void Widget::B4addpressed() { addItem(3); }
void Widget::B5addpressed() { addItem(4); }
void Widget::B1deletepressed() { deleteItem(0); }
void Widget::B2deletepressed() { deleteItem(1); }
void Widget::B3deletepressed() { deleteItem(2); }
void Widget::B4deletepressed() { deleteItem(3); }
void Widget::B5deletepressed() { deleteItem(4); }
void Widget::B1deleteallpressed() { deleteAllItems(0); }
void Widget::B2deleteallpressed() { deleteAllItems(1); }
void Widget::B3deleteallpressed() { deleteAllItems(2); }


void Widget::addItem(int bookmarknumber) {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->addItem(bookmarklist.at(bookmarknumber));
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }

    // QDBusPendingCallWatcher ???
}

void Widget::deleteItem(int bookmarknumber) {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteItem(bookmarklist.at(bookmarknumber).i32Uid);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void Widget::deleteAllItems(int type) {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteAllItems(type);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void Widget::getItems() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::BookmarkItemList> reply = bookmark->getItems("", 1, conn::brw::BST_UNSORTED, 2, 2);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::BookmarkItemList ret2 = reply.argumentAt<1>();

        for (int i = 0; i < ret2.size(); ++i) {
            qDebug() << "BookmarkItemList " << ret2.at(i).i32Uid << ret2.at(i).strTitle << ret2.at(i).strUrl << ret2.at(i).strParentFolderPath;
        }
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void Widget::input() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = userinput->inputText(conn::brw::DR_OK, "test");
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void Widget::reload() {
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
