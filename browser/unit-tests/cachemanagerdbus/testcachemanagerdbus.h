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

#include <QtTest/QtTest>
#include "../../../common/cachemanagerdbus.h"
#include "../../../common/browserdefs.h"

class TestCacheManagerDBus: public QObject
{
	Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testSetGetCacheSize();
    void testSetGetCachePolicy();
    void testGetMaximumCacheSize();
    void testCanClearCache();

private:
   CacheManagerDbus *m_cdb  = NULL;
};
