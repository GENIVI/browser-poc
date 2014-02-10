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

#include <QSignalSpy>
#include <QDebug>
#include <QProcess>

#include "testcachemanagerdbus.h"

//////////// Setup & teardown  /////////////

void TestCacheManagerDBus::initTestCase () {
    m_cdb = new CacheManagerDbus();
    m_cdb->connectdbussession("1");
}

void TestCacheManagerDBus::cleanupTestCase() {
    delete m_cdb;
}

///////////////// Test cases  ///////////////

void TestCacheManagerDBus::testSetGetCacheSize() {
    m_cdb->getCacheSize();
}

void TestCacheManagerDBus::testSetGetCachePolicy() {
    m_cdb->setCachePolicy(conn::brw::CP_CACHE_ONLY);
    QVERIFY(m_cdb->getCachePolicy() == conn::brw::CP_CACHE_ONLY);

    m_cdb->setCachePolicy(conn::brw::CP_ONLINE_ONLY);
    QVERIFY(m_cdb->getCachePolicy() == conn::brw::CP_ONLINE_ONLY);
}

void TestCacheManagerDBus::testGetMaximumCacheSize() {
    m_cdb->getMaximumCacheSize();
}

void TestCacheManagerDBus::testCanClearCache() {
    qulonglong old = m_cdb->getCacheSize();
    m_cdb->clearCache();
    QVERIFY (m_cdb->getCacheSize() <= old);
}

QTEST_MAIN (TestCacheManagerDBus);
