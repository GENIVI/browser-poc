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

#include <QtDBus/QDBusConnection>

#include "browserhelper.h"
#include "ibookmarkmanager_adaptor.h"
#include "iuserinput_adaptor.h"
#include "iwebpagewindow_adaptor.h"
#include "ibrowser_adaptor.h"


browserhelper::browserhelper(QString instanceId, QObject *parent) :
    QObject(parent)
{
    registertypes();

    *connection = QDBusConnection::sessionBus();
    if(!connection->isConnected()) {
        qDebug() << "failed to connect to dbus";
        exit(1);
    }

    QString *dbusservicename = new QString("genivi.poc.browser" + instanceId);
    qDebug() << *dbusservicename;

    if(!connection->registerService(*dbusservicename)) {
        qDebug() << "failed register service " << *dbusservicename;
        exit(1);
    }

    browser *br = new browser();
    new IBrowserAdaptor(br);
    if(!connection->registerObject("/Browser/IBrowser", br)) {
        qDebug() << "failed register object IBrowser";
        exit(1);
    }

    bookmarkmanager *bm = new bookmarkmanager();
    new IBookmarkManagerAdaptor(bm);
    if(!connection->registerObject("/Browser/IBookmarkManager", bm)) {
        qDebug() << "failed register object IBookmarkManager";
        exit(1);
    }

    wpw = new webpagewindow();
    new IWebPageWindowAdaptor(wpw);
    br->wpw = wpw;

    userinput *ui = new userinput();
    new IUserInputAdaptor(ui);
    br->ui = ui;
}

void browserhelper::registertypes() {
    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::BookmarkItem>();
    qDBusRegisterMetaType<conn::brw::BookmarkItemList>();
    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();
    qDBusRegisterMetaType<conn::brw::Rect>();
    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();
    qDBusRegisterMetaType<conn::brw::BrowserActions>();
    qDBusRegisterMetaType<conn::brw::OBJECT_HANDLE>();
    qDBusRegisterMetaType<conn::brw::ObjectHandleList>();
}

