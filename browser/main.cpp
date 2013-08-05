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

#include "../common/browserdefs.h"

//#include <QtDBus/QDBusConnection>
#include <QDBusMetaType>

#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>

#include "browserhelper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Genivi");
    QCoreApplication::setOrganizationDomain("genivi.org");
    QCoreApplication::setApplicationName("Browser PoC");

    browserhelper bh;


    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/browser/main.qml"));
    viewer.showExpanded();

    QObject *object = viewer.rootObject();
    QObject::connect(object, SIGNAL(urlChanged(int, QString)), &bh, SIGNAL(urlChanged(int, QString)));


    bh.webitem = viewer.contentItem()->childItems().at(0);

    qDebug()  << "A" << bh.webitem <<  bh.webitem->childItems();

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
