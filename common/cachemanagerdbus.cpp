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
    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
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


qulonglong CacheManagerDbus::getCacheSize() {
    qDebug() << __PRETTY_FUNCTION__;
    qulonglong ret = 0;

    if (!m_cachemanager){
        qDebug() << "Manager not initialized, call connectdbussession first";
        return ret;
    }

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

conn::brw::CACHE_POLICY CacheManagerDbus::getCachePolicy() {
    qDebug() << __PRETTY_FUNCTION__;

    conn::brw::CACHE_POLICY ret = conn::brw::CP_ONLINE_CACHE;

    if (!m_cachemanager){
        qDebug() << "Manager not initialized, call connectdbussession first";
        return ret;
    }

    QDBusReply<conn::brw::CACHE_POLICY> reply = m_cachemanager->getCachePolicy();

    if(reply.isValid()) {
        ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
    return ret;
}

void CacheManagerDbus::setCachePolicy(conn::brw::CACHE_POLICY policy) {
    qDebug() << __PRETTY_FUNCTION__;

    if (!m_cachemanager){
        qDebug() << "Manager not initialized, call connectdbussession first";
    }

    QDBusReply<conn::brw::ERROR_IDS> reply = m_cachemanager->setCachePolicy(policy);

    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret;
        ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

qulonglong CacheManagerDbus::getMaximumCacheSize() {
    qDebug() << __PRETTY_FUNCTION__;

    qlonglong ret = 0;

    if (!m_cachemanager){
        qDebug() << "Manager not initialized, call connectdbussession first";
        return ret;
    }

    QDBusReply<qulonglong> reply = m_cachemanager->getMaximumCacheSize();

    if(reply.isValid()) {
        ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
    return ret;
}

void CacheManagerDbus::clearCache() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusReply<conn::brw::ERROR_IDS> reply = m_cachemanager->clearCache();

    if (!m_cachemanager){
        qDebug() << "Manager not initialized, call connectdbussession first";
    }

    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret;
        ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}
