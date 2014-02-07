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

#include "cachemanagerdbus.h"

#include "../common/browserdefs.h"

CacheManagerDbus::CacheManagerDbus(QObject *parent) :
    QObject(parent), m_instanceId("1"), m_isconnected(false)
{
    qDebug() << __PRETTY_FUNCTION__;

    registertypes();
}

void CacheManagerDbus::registertypes() {
    qDBusRegisterMetaType<conn::brw::CACHE_POLICY>();
}

void CacheManagerDbus::connectdbussession(QString id) {
    qDebug() << __PRETTY_FUNCTION__ << id;

    m_instanceId = id;

    QString *dbusservicename = new QString("genivi.poc.browser" + m_instanceId);

    m_cachemanager = new conn::brw::ICacheManager(*dbusservicename, "/Browser/ICacheManager",
                                      QDBusConnection::sessionBus(), this);
    m_isconnected = true;
    if(!m_cachemanager->isValid()) {
        qDebug() << "failed create object /Browser/ICacheManager";
        m_isconnected = false;
    }
    connect(m_cachemanager, SIGNAL(onCacheChanged(void)), this, SLOT(cacheChanged(void)));
}


qlonglong CacheManagerDbus::getCacheSize() {
    qDebug() << __PRETTY_FUNCTION__;

    qulonglong ret;
    QDBusReply<qulonglong> reply = m_cachemanager->getCacheSize();

    if(reply.isValid()) {
        ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
    return ret;
}
