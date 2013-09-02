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

#include "../common/browserdbus.h"


#include <QtQml>
#include <QQuickItem>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer *viewer = new QtQuick2ApplicationViewer;

    qmlRegisterType<BrowserDbus>("browserdbusinterface",1,0,"BrowserInterface");
    qmlRegisterType<Bookmark>("browserdbusinterface",1,0,"Tmp");

    viewer->setMainQmlFile(QStringLiteral("qml/demoui/main.qml"));
    viewer->setFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    viewer->setGeometry(0, 0, 800, 80);
    viewer->show();

    QObject::connect((QObject*)viewer->rootObject(), SIGNAL(bookmarksopen(bool)),(QObject*)viewer, SLOT(changeGeometry(bool)));

    return app.exec();
}
