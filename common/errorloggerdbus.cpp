/**
 * Copyright (C) 2014, Pelagicore
 *
 * Author: Jonatan Pålsson <jonatan.palsson@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <QDBusMetaType>
#include <QtQml>
#include <QDBusReply>

#include "errorloggerdbus.h"

#include "../common/browserdefs.h"

ErrorLoggerDbus::ErrorLoggerDbus(QObject *parent) :
    QObject(parent), m_instanceId("1")
{
    qDebug() << __PRETTY_FUNCTION__;

    registertypes();
}

void ErrorLoggerDbus::registertypes() {
    qDBusRegisterMetaType<conn::brw::ErrorItemList>();
    qDBusRegisterMetaType<conn::brw::ErrorItem>();
    qDBusRegisterMetaType<conn::brw::ERROR_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
}

void ErrorLoggerDbus::connectdbussession(QString id) {
    qDebug() << __PRETTY_FUNCTION__ << id;

    m_instanceId = id;

    QString *dbusservicename = new QString("genivi.poc.browser" + m_instanceId);

    m_errorlogger = new conn::brw::IErrorLogger(*dbusservicename, "/Browser/IErrorLogger",
                                      QDBusConnection::sessionBus(), this);
    if(!m_errorlogger->isValid()) {
        qDebug() << "failed create object /Browser/IErrorLogger";
    }

    connect(m_errorlogger, SIGNAL(onNewErrorItem(conn::brw::ErrorItem)),
            this,          SIGNAL(onNewErrorItem(conn::brw::ErrorItem)));
    connect(m_errorlogger, SIGNAL(onErrorListChanged(void)),
            this,          SIGNAL(onErrorListChanged(void)));
}

uint ErrorLoggerDbus::getItemsCount(qlonglong start, qlonglong end) {
    qDebug() << __PRETTY_FUNCTION__;
    uint ret = 0;

    if (!m_errorlogger){
        qDebug() << "ErrorLogger not initialized, call connectdbussession first";
        return ret;
    }

    QDBusReply<uint> reply = m_errorlogger->getItemsCount(start, end);

    if(reply.isValid()) {
        ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
    return ret;
}
conn::brw::ErrorItemList ErrorLoggerDbus::getItems(qlonglong timeFrom,
                                           qlonglong timeTo,
                                           conn::brw::ERROR_SORT_TYPE type,
                                           uint startIndex,
                                           uint itemsCount) {
    qDebug() << __PRETTY_FUNCTION__;
    conn::brw::ErrorItemList list;

    if (!m_errorlogger){
        qDebug() << "ErrorLogger not initialized, call connectdbussession first";
        return list;
    }

    QDBusReply<conn::brw::ERROR_IDS> reply = 
        m_errorlogger->getItems(timeFrom, timeTo, type, startIndex, itemsCount, list);

    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret;
        ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
    for (int i = 0; i < list.size(); i++) {
        qDebug() << "Error item:" << list.at(i).strDescription;
    }
    return list;
}
