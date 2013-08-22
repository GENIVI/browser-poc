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

conn::brw::ERROR_IDS webpagewindow::getBrowserActionsState(conn::brw::BrowserActions &a_browserActionsState) {
    qDebug() << __PRETTY_FUNCTION__;

    conn::brw::BrowserScrollDirections *temp_scrolldirections = new conn::brw::BrowserScrollDirections();
    temp_scrolldirections->u8Left = 1;
    temp_scrolldirections->u8Right = 1;
    temp_scrolldirections->u8Top = 1;
    temp_scrolldirections->u8Bottom = 1;

    conn::brw::BrowserActions *temp_browseractions = new conn::brw::BrowserActions();
    temp_browseractions->u8Back = 0x03;
    temp_browseractions->u8Forward = 0x03;
    temp_browseractions->u8Reload = 0x03;
    temp_browseractions->u8Stop = 0x03;
    temp_browseractions->u8LoadUrl = 0x03;
    temp_browseractions->u8Select = 0x00;
    temp_browseractions->sScrollSymbol = *temp_scrolldirections;
    temp_browseractions->sScrollPage = *temp_scrolldirections;
    temp_browseractions->sScrollLink = *temp_scrolldirections;

    a_browserActionsState = *temp_browseractions;

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::getContentSize(uint &a_u32Width, uint &a_u32Height) {
    qDebug() << __PRETTY_FUNCTION__;

    uint width = webitem->property("contentWidth").toInt();
    uint height = webitem->property("contentHeight").toInt();

    a_u32Width = width;
    a_u32Height = height;

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::getGeometry(conn::brw::Rect &a_sRect) {
    qDebug() << __PRETTY_FUNCTION__;

    a_sRect.i32X = webitem->property("x").toInt();
    a_sRect.i32Y = webitem->property("y").toInt();
    a_sRect.i32Width = webitem->property("width").toInt();
    a_sRect.i32Height = webitem->property("height").toInt();

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::setGeometry(const conn::brw::Rect & a_sRect) {
    qDebug() << __PRETTY_FUNCTION__;

    webitem->setProperty("x", a_sRect.i32X);
    webitem->setProperty("y", a_sRect.i32Y);
    webitem->setProperty("width", a_sRect.i32Width);
    webitem->setProperty("height", a_sRect.i32Height);

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::scroll(conn::brw::SCROLL_DIRECTION a_eScrollDirection, conn::brw::SCROLL_TYPE a_eScrollType) {
    qDebug() << __PRETTY_FUNCTION__;

    int i = 0;
    int scrollheight = (webitem->property("height").toInt())-(webitem->property("contentheight").toInt());
    int scrollwidth = (webitem->property("width").toInt())-(webitem->property("contentwidth").toInt());

    int scrolltype = 50;
    if(a_eScrollType == conn::brw::ST_PAGE)
        scrolltype = webitem->property("height").toInt();

    switch (a_eScrollDirection) {
    case conn::brw::SD_TOP:
        i = webitem->property("y").toInt();
        if(i != 0)
            webitem->setProperty("y", i + scrolltype);
        break;
    case conn::brw::SD_BOTTOM:
        i = webitem->property("y").toInt();
        if(i > scrollheight)
            webitem->setProperty("y", i - scrolltype);
        break;
    case conn::brw::SD_RIGHT:
        i = webitem->property("x").toInt();
        if(i > scrollwidth)
            webitem->setProperty("x", i - scrolltype);
        break;
    case conn::brw::SD_LEFT:
        i = webitem->property("x").toInt();
        if(i != 0)
            webitem->setProperty("x", i + scrolltype);
        break;
    default:
        break;
    }

    return conn::brw::EID_NO_ERROR;
}

bool webpagewindow::getVisible() {
    qDebug() << __PRETTY_FUNCTION__;

    return webitem->property("visible").toBool();
}

conn::brw::ERROR_IDS webpagewindow::setVisible(bool a_bVisible) {
    qDebug() << __PRETTY_FUNCTION__ << a_bVisible;

    webitem->setProperty("visible", a_bVisible);

    return conn::brw::EID_NO_ERROR;
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
