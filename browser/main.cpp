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
#include "browserhelper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Genivi");
    QCoreApplication::setOrganizationDomain("genivi.org");
    QCoreApplication::setApplicationName("Browser PoC");

    browserhelper bhelper;


    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/browser/main.qml"));
    viewer.showExpanded();

    QObject *object = viewer.rootObject();
    QObject::connect(object, SIGNAL(pageLoadStarted(QString)), &bhelper, SLOT(browserStartLoading(QString)));
    QObject::connect(object, SIGNAL(pageLoadFinished(bool)), bhelper.wpw, SIGNAL(onLoadFinished(bool)));

    bhelper.webitem = viewer.contentItem()->childItems().at(0);

    qDebug()  << "A" << bhelper.webitem <<  bhelper.webitem->childItems();

//    QQuickItem *test = viewer.contentItem()->childItems().at(0);
//    qDebug()  << "A" << test << test->childItems();
//    qDebug() << test->setProperty("url", "http://www.google.de");
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

    return app.exec();
}
