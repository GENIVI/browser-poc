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
#include <QTimer>
#include <QDBusMessage>

webpagewindow::webpagewindow(QObject *parent) :
    QObject(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
}

void webpagewindow::browserStartLoading() {
    qDebug() << __PRETTY_FUNCTION__;
    emit onLoadStarted();

    progresstimer = new QTimer(this);
    connect(progresstimer, SIGNAL(timeout()), this, SLOT(reportprogress()));
    progresstimer->start(250);
}

void webpagewindow::reportprogress() {
    qDebug() << __PRETTY_FUNCTION__;
    int progress;
    progress = webitem->getProgress();

    qDebug() << progress;
    emit onLoadProgress(progress);

    if(progress >= 100)
        progresstimer->stop();
}

void webpagewindow::getUrlTitle() {
    qDebug() << webitem->getURL() << webitem->getTitle();

    localurl = webitem->getURL();
    localtitle = webitem->getTitle();
}

conn::brw::ERROR_IDS webpagewindow::back() {
    qDebug() << __PRETTY_FUNCTION__;

    emit setOutputWebview(message().path());

    webitem->goBack();
    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::forward() {
    qDebug() << __PRETTY_FUNCTION__;

    emit setOutputWebview(message().path());

    webitem->goForward();
    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::load(const QString &a_Url) {
    qDebug() << __PRETTY_FUNCTION__ << a_Url;

    // is the url valid?
    if(a_Url == "" || a_Url == "http://")
        return conn::brw::EID_INVALID_ARGUMENT;

    emit setOutputWebview(message().path());

    bool ret = webitem->load(a_Url);
    if(ret)
        return conn::brw::EID_NO_ERROR;
    else
        return conn::brw::EID_INVALID_ARGUMENT;
}

conn::brw::ERROR_IDS webpagewindow::reload() {
    qDebug() << __PRETTY_FUNCTION__;

    emit setOutputWebview(message().path());

    webitem->pageReload();
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

    emit setOutputWebview(message().path());

    uint width = webitem->property("contentWidth").toInt();
    uint height = webitem->property("contentHeight").toInt();

    a_u32Width = width;
    a_u32Height = height;

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::getGeometry(conn::brw::Rect &a_sRect) {
    qDebug() << __PRETTY_FUNCTION__;

    emit setOutputWebview(message().path());

    webitem->setGeometry(a_sRect.i32X, a_sRect.i32Y, a_sRect.i32Width,
                         a_sRect.i32Height);

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::setGeometry(const conn::brw::Rect & a_sRect) {
    qDebug() << __PRETTY_FUNCTION__;

    emit setOutputWebview(message().path());

    webitem->setGeometry(a_sRect.i32X, a_sRect.i32Y, a_sRect.i32Width,
                         a_sRect.i32Height);

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::scroll(conn::brw::SCROLL_DIRECTION a_eScrollDirection, conn::brw::SCROLL_TYPE a_eScrollType) {
    qDebug() << __PRETTY_FUNCTION__;

    emit setOutputWebview(message().path());

    int i = 0;
    int scrollheight = (webitem->property("height").toInt())-(webitem->property("contentheight").toInt());
    int scrollwidth = (webitem->property("width").toInt())-(webitem->property("contentwidth").toInt());

    int scrolltype = 50;
    if(a_eScrollType == conn::brw::ST_PAGE) {
        if(a_eScrollDirection == conn::brw::SD_BOTTOM || a_eScrollDirection == conn::brw::SD_TOP)
            scrolltype = webitem->property("height").toInt();
        else
            scrolltype = webitem->property("width").toInt();
    }

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

    emit setOutputWebview(message().path());

    return webitem->property("visible").toBool();
}

conn::brw::ERROR_IDS webpagewindow::setVisible(bool a_bVisible) {
    qDebug() << __PRETTY_FUNCTION__ << a_bVisible;

    emit setOutputWebview(message().path());

    webitem->setProperty("visible", a_bVisible);
    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::stop() {
    qDebug() << __PRETTY_FUNCTION__;

    emit setOutputWebview(message().path());

    webitem->pageStop();
    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS webpagewindow::getCurrentUrlTitle(QString &url, QString &title) {
    qDebug() << __PRETTY_FUNCTION__;

    url = localurl;
    title = localtitle;

    emit urlTitleReady();
    return conn::brw::EID_NO_ERROR;
}
