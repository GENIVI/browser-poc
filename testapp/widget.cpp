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

#include <QVBoxLayout>
#include <QPushButton>

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    bookmark = new conn::brw::IBookmarkManager("conn.brw.IBookmarkManager", "/bookmarkmanager",
                                               QDBusConnection::sessionBus(), this);

    userinput = new conn::brw::IUserInput("conn.brw.IUserInput", "/userinput",
                                          QDBusConnection::sessionBus(), this);

    webpagewindow = new conn::brw::IWebPageWindow("conn.brw.IWebPageWindow", "/webpagewindow",
                                                  QDBusConnection::sessionBus(), this);

    browser = new conn::brw::IBrowser("conn.brw.IBrowser", "/browser",
                                      QDBusConnection::sessionBus(), this);

    QPushButton *b1 = new QPushButton("AddItem");
    b1->setFixedHeight(50);
    QPushButton *b2 = new QPushButton("DeleteItem");
    b2->setFixedHeight(50);
    QPushButton *b3 = new QPushButton("DeleteAllItems");
    b3->setFixedHeight(50);
    QPushButton *b4 = new QPushButton("GetItems");
    b4->setFixedHeight(50);
    QPushButton *b5 = new QPushButton("UserInput");
    b5->setFixedHeight(50);
    QPushButton *b6 = new QPushButton("Reload");
    b6->setFixedHeight(50);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(b1);
    layout->addWidget(b2);
    layout->addWidget(b3);
    layout->addWidget(b4);
    layout->addWidget(b5);
    layout->addWidget(b6);

    connect(b1, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(b2, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(b3, SIGNAL(clicked()), this, SLOT(deleteAllItems()));
    connect(b4, SIGNAL(clicked()), this, SLOT(getItems()));
    connect(b5, SIGNAL(clicked()), this, SLOT(input()));
    connect(b6, SIGNAL(clicked()), this, SLOT(reload()));
}

Widget::~Widget()
{   
}


void Widget::addItem() {
    qDebug() << __PRETTY_FUNCTION__;

    conn::brw::BookmarkItem test;
    test.i32Uid = 1;
    test.i32Type = 2;
    test.strParentFolderPath = "AAAA";
    test.strTitle = "BBBB";
    test.strUrl = "CCCC";
    test.strIconPath = "DDDD";
    test.strThumbnailPath = "EEEE";

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->addItem(test);
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

void Widget::deleteItem() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteItem(1);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void Widget::deleteAllItems() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteAllItems(1);
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

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->getItems("hallo", 1, conn::brw::BST_UNSORTED, 1, 1);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
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
        qDebug() << "reply " << ret;
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
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}
