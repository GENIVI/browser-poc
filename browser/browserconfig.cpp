/**
 * Copyright (C) 2014, Pelagicore
 *
 * Author: Jonatan Palsson <jonatan.palsson@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <QDebug>

#include "browserconfig.h"

template void      BrowserConfig::setValue<int>(BrowserConfig::BrowserConfigKey, int);
template void      BrowserConfig::setValue<QString>(BrowserConfig::BrowserConfigKey, QString);
template void      BrowserConfig::setValue<qlonglong>(BrowserConfig::BrowserConfigKey, qlonglong);
template void      BrowserConfig::setValue<qulonglong>(BrowserConfig::BrowserConfigKey, qulonglong);
template void      BrowserConfig::setValue<conn::brw::CACHE_POLICY>(BrowserConfig::BrowserConfigKey, conn::brw::CACHE_POLICY);

template int       BrowserConfig::getValue<int>(BrowserConfig::BrowserConfigKey);
template QString   BrowserConfig::getValue<QString>(BrowserConfig::BrowserConfigKey);
template qlonglong BrowserConfig::getValue<qlonglong>(BrowserConfig::BrowserConfigKey);
template qulonglong BrowserConfig::getValue<qulonglong>(BrowserConfig::BrowserConfigKey);
template conn::brw::CACHE_POLICY BrowserConfig::getValue<conn::brw::CACHE_POLICY>(BrowserConfig::BrowserConfigKey);

BrowserConfig::BrowserConfig() {
    m_qsettings = new QSettings("browserpoc");
}

template<typename T>
T BrowserConfig::getValue(BrowserConfig::BrowserConfigKey key) {
    return m_qsettings->value(QString(key)).value<T>();
}

template<typename T>
void BrowserConfig::setValue(BrowserConfig::BrowserConfigKey key, T value) {
    m_qsettings->setValue(QString(key), value);
    m_qsettings->sync();
}

bool BrowserConfig::contains(BrowserConfig::BrowserConfigKey key) {
    return m_qsettings->contains(QString(key));
}
