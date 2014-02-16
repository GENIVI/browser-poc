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

#ifndef CACHEMANAGERDBUS_H
#define CACHEMANAGERDBUS_H

#include <QObject>
#include <QQmlListProperty>

#include "icachemanager_interface.h"
#include "../common/bookmark.h"
#include "browserdefs.h"

class CacheManagerDbus : public QObject
{
    Q_OBJECT

public:
    explicit CacheManagerDbus(QObject *parent = 0);

    Q_INVOKABLE void connectdbussession(QString id);
    Q_INVOKABLE qulonglong getCacheSize();
    Q_INVOKABLE conn::brw::CACHE_POLICY getCachePolicy();
    Q_INVOKABLE void setCachePolicy(conn::brw::CACHE_POLICY);
    Q_INVOKABLE qulonglong getMaximumCacheSize();
    Q_INVOKABLE void clearCache();

signals:
    void onCacheChanged();

private:
    QString m_instanceId;
    bool m_isconnected;
    conn::brw::ICacheManager *m_cachemanager = NULL;

    void registertypes();
};

#endif // CACHEMANAGERDBUS_H
