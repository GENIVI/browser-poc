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

#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <QObject>
#include <QDBusContext>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include "browserconfig.h"
#include "../common/browserdefs.h"

class cachemanager : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    cachemanager(QObject *parent = 0);
    QNetworkAccessManager *getNetworkAccessManager();
    QNetworkRequest::CacheLoadControl getCacheLoadControl();

signals:
    void cacheChanged();

public Q_SLOTS:
    qlonglong getCacheSize();
    conn::brw::CACHE_POLICY getCachePolicy();
    qlonglong               getMaximumCacheSize();
    conn::brw::ERROR_IDS    setCachePolicy(conn::brw::CACHE_POLICY);
    conn::brw::ERROR_IDS    clearCache();

private:
    BrowserConfig *m_config = NULL;
    conn::brw::CACHE_POLICY m_policy;
    QNetworkAccessManager *m_manager = NULL;
};

#endif // CACHEMANAGER_H
