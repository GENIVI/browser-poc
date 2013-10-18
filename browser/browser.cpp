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

#include "browser.h"
#include <QDebug>

browser::browser(QObject *parent) :
    QObject(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
}

conn::brw::ERROR_IDS browser::createPageWindow(int a_eDeviceId, const conn::brw::Rect & a_oGeometry, conn::brw::OBJECT_HANDLE &a_hPageWindowHandle) {
    qDebug() << __PRETTY_FUNCTION__;

    Q_UNUSED(a_eDeviceId);

    if(windowhash.isEmpty()) {

        initialview = new QDeclarativeView;
        initialview->setSource(QUrl::fromLocalFile("qml/browser/main.qml"));
        initialview->setWindowFlags(Qt::CustomizeWindowHint);

        initialview->setGeometry(a_oGeometry.i32X, a_oGeometry.i32Y, a_oGeometry.i32Width, a_oGeometry.i32Height);
        a_hPageWindowHandle = initialview->winId();
        windowhash.insert(a_hPageWindowHandle, initialview->window());
        initialview->show();

        rootqmlobject = initialview->rootObject();
        wpw->webitem = rootqmlobject;

        connect(rootqmlobject, SIGNAL(pageLoadStarted()), wpw, SLOT(browserStartLoading()));
        connect(rootqmlobject, SIGNAL(pageLoadFinished(bool)), wpw, SIGNAL(onLoadFinished(bool)));
        connect(rootqmlobject, SIGNAL(pageLoadFinished(bool)), wpw, SLOT(getUrlTitle()));
        connect(rootqmlobject, SIGNAL(onInputText(QString, QString, int, int, int, int, int)), ui, SLOT(inputTextReceived(QString, QString, int, int, int, int, int)));

        connect(this, SIGNAL(onPageWindowDestroyed(qlonglong)), wpw, SIGNAL(onClose()));

        connect(ui, SIGNAL(inputText(QString)), this, SLOT(inputText(QString)));

    } else {
        QDeclarativeView *tempview = new QDeclarativeView();
        tempview->setSource(QUrl::fromLocalFile("qml/browser/main.qml"));
        tempview->setWindowFlags(Qt::CustomizeWindowHint);
        tempview->setGeometry(a_oGeometry.i32X, a_oGeometry.i32Y, a_oGeometry.i32Width, a_oGeometry.i32Height);
        a_hPageWindowHandle = tempview->winId();
        windowhash.insert(a_hPageWindowHandle, tempview->window());
        tempview->show();
    }



    QString *webpagewindowservice = new QString("/Browser/IWebPageWindow" + QString::number(a_hPageWindowHandle));
    qDebug() << *webpagewindowservice;

    qDebug() << connection->isConnected();

    if(!connection->registerObject(*webpagewindowservice, wpw)) {
        qDebug() << "failed register object IWebPageWindow";
        exit(1);
    }

    QString *userinputservice = new QString( *webpagewindowservice + "/IUserInput");
    qDebug() << *userinputservice;
    if(!connection->registerObject(*userinputservice, ui)) {
        qDebug() << "failed register object IUserInput";
        exit(1);
    }



    emit onPageWindowCreated(a_hPageWindowHandle, conn::brw::EID_NO_ERROR);
    return conn::brw::EID_NO_ERROR;
}

void browser::inputText(QString input) {
    wpw->webitem->setProperty("input", input);
    wpw->webitem->metaObject()->invokeMethod(wpw->webitem, "inputText");
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
