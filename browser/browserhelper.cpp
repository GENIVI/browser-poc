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
#include "userinput.h"
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
    br->connection = connection;
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

    br->initialview = new QDeclarativeView;
    br->initialview->setSource(QUrl::fromLocalFile("qml/browser/main.qml"));
    br->initialview->setWindowFlags(Qt::CustomizeWindowHint);
//    br->initialview->show();

    QGraphicsObject *rootqmlobject = br->initialview->rootObject();
    webitem = rootqmlobject;
    wpw->webitem = rootqmlobject;

    connect(rootqmlobject, SIGNAL(pageLoadStarted()), this, SLOT(browserStartLoading()));
    connect(rootqmlobject, SIGNAL(pageLoadFinished(bool)), this->wpw, SIGNAL(onLoadFinished(bool)));
    connect(rootqmlobject, SIGNAL(pageLoadFinished(bool)), this->wpw, SIGNAL(urlTitleReady()));
    connect(rootqmlobject, SIGNAL(onInputText(QString, QString, int, int, int, int, int)), ui, SLOT(inputTextReceived(QString, QString, int, int, int, int, int)));

    connect(wpw, SIGNAL(reloadrequested()), this, SLOT(browserreload()));
    connect(wpw, SIGNAL(stoprequested()), this, SLOT(browserstop()));
    connect(wpw, SIGNAL(backrequested()), this, SLOT(browserback()));
    connect(wpw, SIGNAL(forwardrequested()), this, SLOT(browserforward()));
    connect(wpw, SIGNAL(loadurlrequested(QString)), this, SLOT(browserloadurl(QString)));
    connect(wpw, SIGNAL(urlTitleReady()), this, SLOT(getUrlTitle()));

    connect(this, SIGNAL(onLoadStarted()), wpw, SIGNAL(onLoadStarted()));
    connect(this, SIGNAL(onLoadProgress(int)), wpw, SIGNAL(onLoadProgress(int)));

    connect(br, SIGNAL(onPageWindowDestroyed(qlonglong)), wpw, SIGNAL(onClose()));

    connect(ui, SIGNAL(inputText(QString)), this, SLOT(inputText(QString)));
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

void browserhelper::inputText(QString input) {
    webitem->setProperty("input", input);
    webitem->metaObject()->invokeMethod(webitem, "inputText");
}

void browserhelper::browserreload() {
    webitem->metaObject()->invokeMethod(webitem, "pagereload");
}

void browserhelper::browserback() {
    webitem->metaObject()->invokeMethod(webitem, "goBack");
}

void browserhelper::browserforward() {
    webitem->metaObject()->invokeMethod(webitem, "goForward");
}

void browserhelper::browserstop() {
    webitem->metaObject()->invokeMethod(webitem, "pagestop");
}

void browserhelper::browserloadurl(QString url) {
    webitem->setProperty("url", url);
}

void browserhelper::getUrlTitle() {
    qDebug() << webitem->property("url") << webitem->property("title");

    wpw->localurl = webitem->property("url").toString();
    wpw->localtitle = webitem->property("title").toString();
}

void browserhelper::reportprogress() {
    qDebug() << __PRETTY_FUNCTION__;
    int progress;

    progress = webitem->property("progress").toFloat() * 100;

    qDebug() << progress;
    emit onLoadProgress(progress);

    if(progress >= 100)
        progresstimer->stop();
}

void browserhelper::browserStartLoading() {
    qDebug() << __PRETTY_FUNCTION__;
    emit onLoadStarted();

    progresstimer = new QTimer(this);
    connect(progresstimer, SIGNAL(timeout()), this, SLOT(reportprogress()));
    progresstimer->start(250);
}
