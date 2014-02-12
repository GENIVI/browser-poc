/**
 * Copyright (C) 2013, Pelagicore
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

#include <QObject>
#include <QDBusContext>
#include <QDebug>
#include <QAbstractNetworkCache>
#include <QNetworkDiskCache>

#include "cachemanager.h"
#include "../common/browserdefs.h"

cachemanager::cachemanager(QObject *parent) :
    QObject(parent)
{
    m_config = new BrowserConfig();
    m_manager = new QNetworkAccessManager();
    QNetworkDiskCache *cache = new QNetworkDiskCache();
    cache->setCacheDirectory ("/tmp/browserpoc_cache");
    if (cache)
        m_manager->setCache(cache);
    else
        qDebug() << "Unable to create cache file!";

    if (m_config && m_config->contains(BrowserConfig::CONFIG_CACHEPOLICY)) {
        conn::brw::CACHE_POLICY policy = conn::brw::CP_ONLINE_CACHE;
        switch (m_config->getValue<int>(BrowserConfig::CONFIG_CACHEPOLICY))
        {
            case 0:
                policy = conn::brw::CP_ONLINE_CACHE;
                break;
            case 1:
                policy = conn::brw::CP_CACHE_ONLY;
                break;
            case 2:
                policy = conn::brw::CP_ONLINE_ONLY;
                break;
        }
        qDebug() << "Reading cachePolicy from config:" << policy;
        this->setCachePolicy(policy);
    }
}

qulonglong cachemanager::getCacheSize(){
    qDebug() << "Getting cache size";
    if (!m_manager->cache()) {
        qDebug() << "Unable to retreive cache!";
        return 0;
    }
    return m_manager->cache()->cacheSize();
}

conn::brw::CACHE_POLICY cachemanager::getCachePolicy(){
    qDebug() << "Getting cache policy";
    return m_policy;
}

qulonglong cachemanager::getMaximumCacheSize(){
    if (!m_manager->cache()) {
        qDebug() << "Unable to retreive cache!";
        return 0;
    }
    QNetworkDiskCache *cache = qobject_cast<QNetworkDiskCache *>(m_manager->cache());
    if (cache)
        return cache->maximumCacheSize();
    else {
        qDebug() << "Unable to retrieve max cache size";
        return 0;
    }
}

conn::brw::ERROR_IDS cachemanager::setCachePolicy(conn::brw::CACHE_POLICY pol)
{
    qDebug() << "Setting cache policy:" << pol;
    m_config->setValue(BrowserConfig::CONFIG_CACHEPOLICY, pol);
    m_policy = pol;
    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS cachemanager::clearCache()
{
    m_manager->cache()->clear();
    return conn::brw::EID_NO_ERROR;
}

QNetworkAccessManager *cachemanager::getNetworkAccessManager()
{
    return m_manager;
}

QNetworkRequest::CacheLoadControl cachemanager::getCacheLoadControl()
{
    switch (m_policy) {
        case conn::brw::CP_ONLINE_CACHE:
            return QNetworkRequest::PreferCache;
        case conn::brw::CP_CACHE_ONLY:
            return QNetworkRequest::AlwaysCache;
        case conn::brw::CP_ONLINE_ONLY:
            return QNetworkRequest::AlwaysNetwork;
        default:
            qDebug() << "Illegal cache policy!";
            return QNetworkRequest::PreferCache;
    }
}
