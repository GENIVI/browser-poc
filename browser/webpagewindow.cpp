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

#include "webpagewindow.h"
#include <QDebug>

webpagewindow::webpagewindow(QObject *parent) :
    QObject(parent)
{
    qDebug() << __PRETTY_FUNCTION__;


}

conn::brw::ERROR_IDS webpagewindow::back() {
    qDebug() << __PRETTY_FUNCTION__;

    emit backrequested();

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::forward() {
    qDebug() << __PRETTY_FUNCTION__;

    emit forwardrequested();

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::getBrowserActionsState(conn::brw::BrowserActions &a_browserActionsState) {
    qDebug() << __PRETTY_FUNCTION__;

    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS webpagewindow::getContentSize(uint &a_u32Width, uint &a_u32Height) {
    qDebug() << __PRETTY_FUNCTION__;

    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS webpagewindow::getGeometry(conn::brw::Rect &a_sRect) {
    qDebug() << __PRETTY_FUNCTION__;

    return conn::brw::EID_NOT_IMPLEMENTED;
}

bool webpagewindow::getVisible() {
    qDebug() << __PRETTY_FUNCTION__;

    return false;
}

conn::brw::ERROR_IDS webpagewindow::load(const QString &a_Url) {
    qDebug() << __PRETTY_FUNCTION__ << a_Url;

    emit loadurlrequested(a_Url);

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::reload() {
    qDebug() << __PRETTY_FUNCTION__;


    emit reloadrequested();

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::scroll(conn::brw::SCROLL_DIRECTION a_eScrollDirection, conn::brw::SCROLL_TYPE a_eScrollType) {
    qDebug() << __PRETTY_FUNCTION__;

    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS webpagewindow::setGeometry(const conn::brw::Rect & a_sRect) {
    qDebug() << __PRETTY_FUNCTION__;

    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS webpagewindow::setVisible(bool a_bVisible) {
    qDebug() << __PRETTY_FUNCTION__;

    return conn::brw::EID_NOT_IMPLEMENTED;
}

conn::brw::ERROR_IDS webpagewindow::stop() {
    qDebug() << __PRETTY_FUNCTION__;

    emit stoprequested();

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::getCurrentUrlTitle(QString &url, QString &title) {
    qDebug() << __PRETTY_FUNCTION__;

    emit urlTitleReady();

    url = localurl;
    title = localtitle;

    return conn::brw::EID_NO_ERROR;
}

void webpagewindow::loadforward(int status, QString url) {
    qDebug() << __PRETTY_FUNCTION__;

    emit onLoadStarted(url);
}
