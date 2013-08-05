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

#include "browserhelper.h"

#include <QtDBus/QDBusConnection>
//#include <QDBusMetaType>

#include "bookmarkmanager.h"
#include "ibookmarkmanager_adaptor.h"

#include "userinput.h"
#include "iuserinput_adaptor.h"

//#include "webpagewindow.h"
#include "iwebpagewindow_adaptor.h"

#include "browser.h"
#include "ibrowser_adaptor.h"

browserhelper::browserhelper(QObject *parent) :
    QObject(parent)
{

    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::BookmarkItem>();
    qDBusRegisterMetaType<conn::brw::BookmarkItemList>();

    bookmarkmanager *bm = new bookmarkmanager();
    new IBookmarkManagerAdaptor(bm);

    QDBusConnection connection = QDBusConnection::sessionBus();
    if(!connection.registerService("conn.brw.IBookmarkManager"))
        qDebug() << "failed register service conn.brw.IBookmarkManager";
    if(!connection.registerObject("/bookmarkmanager", bm))
        qDebug() << "failed register object bookmarkmanager";


    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();

    userinput *ui = new userinput();
    new IUserInputAdaptor(ui);

    if(!connection.registerService("conn.brw.IUserInput"))
        qDebug() << "failed register service conn.brw.IUserInput";
    if(!connection.registerObject("/userinput", ui))
        qDebug() << "failed register object userinput";


    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();

    wpw = new webpagewindow();
    new IWebPageWindowAdaptor(wpw);

    if(!connection.registerService("conn.brw.IWebPageWindow"))
        qDebug() << "failed register service conn.brw.IWebPageWindow";
    if(!connection.registerObject("/webpagewindow", wpw))
        qDebug() << "failed register object userinput";


    browser *br = new browser();
    new IBrowserAdaptor(br);

    if(!connection.registerService("conn.brw.IBrowser"))
        qDebug() << "failed register service conn.brw.IBrowser";
    if(!connection.registerObject("/browser", br))
        qDebug() << "failed register object browser";


    connect(wpw, SIGNAL(reloadrequested()), this, SLOT(browserreload()));
    connect(wpw, SIGNAL(stoprequested()), this, SLOT(browserstop()));
    connect(wpw, SIGNAL(backrequested()), this, SLOT(browserback()));
    connect(wpw, SIGNAL(forwardrequested()), this, SLOT(browserforward()));
    connect(wpw, SIGNAL(loadurlrequested(QString)), this, SLOT(browserloadurl(QString)));

    connect(wpw, SIGNAL(urlTitleReady()), this, SLOT(getUrlTitle()));

    connect(this, SIGNAL(onLoadStarted(QString)), wpw, SIGNAL(onLoadStarted(QString)));

    connect(this, SIGNAL(onLoadProgress(int)), wpw, SIGNAL(onLoadProgress(int)));

}

void browserhelper::browserreload() {
    QMetaObject::invokeMethod(webitem, "reload");
}

void browserhelper::browserback() {
    QMetaObject::invokeMethod(webitem, "goBack");
}

void browserhelper::browserforward() {
    QMetaObject::invokeMethod(webitem, "goForward");
}

void browserhelper::browserstop() {
    QMetaObject::invokeMethod(webitem, "stop");
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
    int progress;

    progress = webitem->property("loadProgress").toInt();

    qDebug() << progress;
    emit onLoadProgress(progress);

    if(progress >= 100)
        progresstimer->stop();


}

void browserhelper::browserStartLoading(QString url) {
    qDebug() << __PRETTY_FUNCTION__;
    emit onLoadStarted(url);


    progresstimer = new QTimer(this);
    connect(progresstimer, SIGNAL(timeout()), this, SLOT(reportprogress()));
    progresstimer->start(250);
}
