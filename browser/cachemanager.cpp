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

#include "cachemanager.h"
#include "../common/browserdefs.h"

cachemanager::cachemanager(QObject *parent) : 
    QObject(parent)
{
    m_config = new BrowserConfig();
}

qlonglong cachemanager::getCacheSize(){
    return m_config->getValue<qlonglong>(BrowserConfig::CONFIG_CACHESIZE);
}

conn::brw::CACHE_POLICY cachemanager::getCachePolicy(){
    qDebug() << "Getting cache policy";
    return conn::brw::CP_CACHE_ONLY;
}
qlonglong cachemanager::getMaximumCacheSize(){}
conn::brw::ERROR_IDS cachemanager::setCachePolicy(conn::brw::CACHE_POLICY pol)
{
    emit onCachePolicyChanged(pol);
    qDebug() << "TODO: setCachePolicy";
}
conn::brw::ERROR_IDS cachemanager::clearCache()
{
    emit onClearCache();
    qDebug() << "TODO: clearCache";
}
