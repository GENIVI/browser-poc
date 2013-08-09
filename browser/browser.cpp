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
        initialview->setGeometry(a_oGeometry.i32X, a_oGeometry.i32Y, a_oGeometry.i32Width, a_oGeometry.i32Height);
        a_hPageWindowHandle = initialview->winId();
        windowhash.insert(a_hPageWindowHandle, initialview->window());
        initialview->show();
    } else {
        QDeclarativeView *tempview = new QDeclarativeView();
        tempview->setSource(QUrl::fromLocalFile("qml/browser/main.qml"));
        tempview->setWindowFlags(Qt::CustomizeWindowHint);
        tempview->setGeometry(a_oGeometry.i32X, a_oGeometry.i32Y, a_oGeometry.i32Width, a_oGeometry.i32Height);
        a_hPageWindowHandle = tempview->winId();
        windowhash.insert(a_hPageWindowHandle, tempview->window());
        tempview->show();
    }

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS browser::destroyPageWindow(conn::brw::OBJECT_HANDLE a_hPageWindowHandle) {
    qDebug() << __PRETTY_FUNCTION__ << a_hPageWindowHandle;

    if(!windowhash.isEmpty()) {
        QWidget *tempwidget = windowhash.value(a_hPageWindowHandle);
        windowhash.remove(a_hPageWindowHandle);
        tempwidget->hide();
        return conn::brw::EID_NO_ERROR;
    }
    return conn::brw::EID_GENERAL_ERROR;
}

conn::brw::ERROR_IDS browser::getPageWindows(conn::brw::ObjectHandleList &a_oPageWindowIds) {
    qDebug() << __PRETTY_FUNCTION__;

    a_oPageWindowIds = windowhash.keys();

    return conn::brw::EID_NO_ERROR;
}
