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

conn::brw::ERROR_IDS browser::createPageWindow(int a_eDeviceId, const conn::brw::Rect & a_oGeometry, qlonglong &a_hPageWindowHandle) {
    qDebug() << __PRETTY_FUNCTION__;

    emit createPage(a_oGeometry.i32X, a_oGeometry.i32Y, a_oGeometry.i32Width, a_oGeometry.i32Height);

    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS browser::destroyPageWindow(qlonglong a_hPageWindowHandle) {
    qDebug() << __PRETTY_FUNCTION__;

    emit destroyPage();

    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS browser::getPageWindows(conn::brw::ObjectHandleList &a_oPageWindowIds) {
    qDebug() << __PRETTY_FUNCTION__;
    return conn::brw::EID_NOT_IMPLEMENTED;
}
