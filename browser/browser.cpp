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

#include <QDebug>
#include <QDBusConnection>
#include <QFile>

#include "browser.h"
#include "browserview.h"

browser::browser(QObject *parent) :
    QObject(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
}

conn::brw::ERROR_IDS browser::createPageWindow(int a_eDeviceId, const conn::brw::Rect & a_oGeometry, conn::brw::OBJECT_HANDLE &a_hPageWindowHandle) {
    qDebug() << __PRETTY_FUNCTION__;

    Q_UNUSED(a_eDeviceId);

    BrowserView *bvi = new BrowserView();
    bvi->setGeometry(a_oGeometry.i32X, a_oGeometry.i32Y, a_oGeometry.i32Width,
                         a_oGeometry.i32Height);
    bvi->show();
    a_hPageWindowHandle = bvi->winId();

    windowhash.insert(a_hPageWindowHandle, bvi->window());

    wpw->webitem = bvi;
    connect(bvi,  SIGNAL(pageLoadFinished(bool)),       wpw,  SLOT(getUrlTitle()));
    connect(ui,   SIGNAL(inputText(QString)),           this, SLOT(inputText(QString)));
    connect(bvi,  SIGNAL(pageLoadStarted()),            wpw,  SLOT(browserStartLoading()));
    connect(bvi,  SIGNAL(pageLoadFinished(bool)),       wpw,  SIGNAL(onLoadFinished(bool)));
    connect(bvi,  SIGNAL(onUrlChanged(QString)),        wpw,  SIGNAL(onUrlChanged(QString)));
    connect(bvi,  SIGNAL(onTitleChanged(QString)),      wpw,  SIGNAL(onTitleChanged(QString)));
    connect(bvi,  SIGNAL(onLinkClicked(QString)),       wpw,  SIGNAL(onLinkClicked(QString)));
    connect(bvi,  SIGNAL(onSelectionChanged(void)),     wpw,  SIGNAL(onSelectionChanged(void)));
    connect(bvi,  SIGNAL(onStatusTextChanged(QString)), wpw,  SIGNAL(onStatusTextChanged(QString)));
    connect(bvi,  SIGNAL(onInputText(QString, QString, int, int, int, int, int)), ui, SLOT(inputTextReceived(QString, QString, int, int, int, int, int)));
    connect(this, SIGNAL(onPageWindowDestroyed(qlonglong)), wpw, SIGNAL(onClose()));

    QString *webpagewindowservice = new QString("/Browser/IWebPageWindow" + QString::number(a_hPageWindowHandle));
    qDebug() << *webpagewindowservice;

    webviewhash.insert(*webpagewindowservice, bvi);

    QDBusConnection conn = connection();
    if(!conn.registerObject(*webpagewindowservice, wpw)) {
        qDebug() << "failed register object IWebPageWindow";
        exit(1);
    }

    QString *userinputservice = new QString( *webpagewindowservice + "/IUserInput");
    qDebug() << *userinputservice;
    if(!conn.registerObject(*userinputservice, ui)) {
        qDebug() << "failed register object IUserInput";
        exit(1);
    }

    emit onPageWindowCreated(a_hPageWindowHandle, conn::brw::EID_NO_ERROR);
    return conn::brw::EID_NO_ERROR;
}

void browser::setView(QString viewpath) {
    qDebug() << __PRETTY_FUNCTION__ << viewpath;

    if(viewpath.contains("/IUserInput"))
        wpw->webitem = webviewhash.value(viewpath.remove("/IUserInput"));
    else
        wpw->webitem = webviewhash.value(viewpath);
}

void browser::inputText(QString input) {
    qDebug() << __PRETTY_FUNCTION__ << input;

    wpw->webitem->inputText(input);
}

conn::brw::ERROR_IDS browser::destroyPageWindow(conn::brw::OBJECT_HANDLE a_hPageWindowHandle) {
    qDebug() << __PRETTY_FUNCTION__ << a_hPageWindowHandle;

    if(!windowhash.isEmpty()) {
        QWidget *tempwidget = windowhash.value(a_hPageWindowHandle);
        if(tempwidget) {
            windowhash.remove(a_hPageWindowHandle);
            tempwidget->hide();
            emit onPageWindowDestroyed(a_hPageWindowHandle);
            return conn::brw::EID_NO_ERROR;
        }
        return conn::brw::EID_DB_ITEM_NOT_EXISTS;
    }
    return conn::brw::EID_NOT_EXISTS;
}

conn::brw::ERROR_IDS browser::getPageWindows(conn::brw::ObjectHandleList &a_oPageWindowIds) {
    qDebug() << __PRETTY_FUNCTION__;

    conn::brw::ERROR_IDS ret;

    if(windowhash.isEmpty()) {
        ret = conn::brw::EID_NOT_EXISTS;
    } else {
        a_oPageWindowIds = windowhash.keys();
        ret =  conn::brw::EID_NO_ERROR;
    }
    return ret;
}
