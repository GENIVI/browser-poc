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

#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include "../browserdefs.h"

//#include <QtDBus/QDBusConnection>
#include <QDBusMetaType>

//#include "bookmarkmanager.h"
//#include "ibookmarkmanager_adaptor.h"

//#include "userinput.h"
//#include "iuserinput_adaptor.h"

//#include "webpagewindow.h"
//#include "iwebpagewindow_adaptor.h"

//#include "browser.h"
//#include "ibrowser_adaptor.h"


#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>

#include "browserhelper.h"



#include "bookmark.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    browserhelper bh;


    QtQuick2ApplicationViewer viewer;

//     ApplicationData data;
//     viewer.rootContext()->setContextProperty("applicationData", &data);
     //    viewer.rootContext()->setContextProperty("currentDateTime", QDateTime::currentDateTime());



    viewer.setMainQmlFile(QStringLiteral("qml/browser/main.qml"));
    viewer.showExpanded();

    bh.item = viewer.contentItem()->childItems().at(0);

    qDebug()  << "A" << bh.item <<  bh.item->childItems();

//    QQuickItem *test = viewer.contentItem()->childItems().at(0);
//    qDebug()  << "A" << test << test->childItems();

//    qDebug() << test->setProperty("url", "http://www.google.de");
//    bh.item->setProperty("test", 3);
//    qDebug() << "E" << test->metaObject()->methodCount() << test->metaObject()->propertyCount();
//    int j = test->metaObject()->propertyCount();

//    for (int i = 0; i < j; i++)
//        qDebug() << i << " " << test->metaObject()->property(i).name();


//    int k = test->metaObject()->methodCount();
//    for (int l = 0; l < k; l++)
//        qDebug() << l  << " " << test->metaObject()->method(l).name() << k;

//    qDebug() << "F" << test->metaObject()->property(79).name();

//    char array[5] = "stop";
//    qDebug() << "G" << test->metaObject()->indexOfMethod(array);

//    test->metaObject()->method(99);




    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::BookmarkItem>();
    qDBusRegisterMetaType<conn::brw::BookmarkItemList>();

//    bookmarkmanager *bm = new bookmarkmanager();
//    new IBookmarkManagerAdaptor(bm);

//    QDBusConnection connection = QDBusConnection::sessionBus();
//    if(!connection.registerService("conn.brw.IBookmarkManager"))
//        qDebug() << "failed register service conn.brw.IBookmarkManager";
//    if(!connection.registerObject("/bookmarkmanager", bm))
//        qDebug() << "failed register object bookmarkmanager";


    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();

//    userinput *ui = new userinput();
//    new IUserInputAdaptor(ui);

//    if(!connection.registerService("conn.brw.IUserInput"))
//        qDebug() << "failed register service conn.brw.IUserInput";
//    if(!connection.registerObject("/userinput", ui))
//        qDebug() << "failed register object userinput";


    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();

//    webpagewindow *wpw = new webpagewindow();
//    new IWebPageWindowAdaptor(wpw);

//    if(!connection.registerService("conn.brw.IWebPageWindow"))
//        qDebug() << "failed register service conn.brw.IWebPageWindow";
//    if(!connection.registerObject("/webpagewindow", wpw))
//        qDebug() << "failed register object userinput";


//    browser *br = new browser();
//    new IBrowserAdaptor(br);

//    if(!connection.registerService("conn.brw.IBrowser"))
//        qDebug() << "failed register service conn.brw.IBrowser";
//    if(!connection.registerObject("/browser", br))
//        qDebug() << "failed register object browser";


    return app.exec();
}
