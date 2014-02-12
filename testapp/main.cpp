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

#include <QApplication>
#include <QQuickWindow>
#include <QtQml>
#include "../common/browserdbus.h"
#include "../common/cachemanagerdbus.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BrowserDbus>("browserdbusinterface",1,0,"BrowserInterface");
    qmlRegisterType<CacheManagerDbus>("browserdbusinterface",1,0,"CacheManagerInterface");
    qmlRegisterType<Bookmark>("browserdbusinterface",1,0,"Tmp");

    QQmlApplicationEngine engine("qml/testapp/main.qml");

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if ( !window ) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }
    window->show();

    return app.exec();
}
