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

#include <QtDBus/QDBusConnection>
#include <QDBusMetaType>

#include "bookmarkmanager.h"
#include "ibookmarkmanager_adaptor.h"

#include "userinput.h"
#include "iuserinput_adaptor.h"

#include "webpagewindow.h"
#include "iwebpagewindow_adaptor.h"

#include "browser.h"
#include "ibrowser_adaptor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/browser/main.qml"));
    viewer.showExpanded();

    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::BookmarkItem>();

    bookmarkmanager *bm = new bookmarkmanager();

    new IBookmarkManagerAdaptor(bm);
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerService("conn.brw.IBookmarkManager");
    connection.registerObject("/bookmarkmanager", bm);


    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();

    userinput *ui = new userinput();

    new IUserInputAdaptor(ui);


    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();
    qDBusRegisterMetaType<conn::brw::Rect>();

    webpagewindow *wpw = new webpagewindow();

    new IWebPageWindowAdaptor(wpw);


    browser *br = new browser();

    new IBrowserAdaptor(br);


    return app.exec();
}
