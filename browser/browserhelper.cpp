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
#include "ibrowser_adaptor.h"
#include "icachemanager_adaptor.h"
#include "ierrorlogger_adaptor.h"
#include "inetworkmanager_adaptor.h"


browserhelper::browserhelper(QString instanceId, QObject *parent) :
    QObject(parent)
{
    registertypes();

    connection = new QDBusConnection(QDBusConnection::sessionBus());
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

    errorlogger *err = errorlogger::instance();
    new IErrorLoggerAdaptor(err);
    if(!connection->registerObject("/Browser/IErrorLogger", err)) {
        qDebug() << "failed register object IErrorLogger";
        exit(1);
    }

    cachemanager *cm = new cachemanager();
    new ICacheManagerAdaptor(cm);
    if(!connection->registerObject("/Browser/ICacheManager", cm)) {
        qDebug() << "failed register object ICacheManager";
        exit(1);
    }

    networkmanager *nm = new networkmanager(cm->getNetworkAccessManager());
    new INetworkManagerAdaptor(nm);
    if(!connection->registerObject("/Browser/INetworkManager", nm)) {
        qDebug() << "failed register object INetworkManager";
        exit(1);
    }

    browser *br = new browser(cm, nm);
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
    qDBusRegisterMetaType<conn::brw::CACHE_POLICY>();
    qDBusRegisterMetaType<conn::brw::AuthenticationData>();
    qDBusRegisterMetaType<conn::brw::SelectableOption>();
    qDBusRegisterMetaType<conn::brw::SelectableOptionList>();
    qDBusRegisterMetaType<conn::brw::SslError>();
    qDBusRegisterMetaType<conn::brw::ErrorItemList>();
    qDBusRegisterMetaType<conn::brw::ErrorItem>();
    qDBusRegisterMetaType<conn::brw::ERROR_SORT_TYPE>();
}

