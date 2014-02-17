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
#ifndef TESTERRORLOGGERDBUS_H
#define TESTERRORLOGGERDBUS_H

#include <QtTest/QtTest>
#include <QDBusConnection>

#include "../../../common/errorloggerdbus.h"
#include "../../../common/browserdefs.h"

#include "ierrorlogger_interface.h"
#include "ierrorlogger_adaptor.h"
#include "../../errorlogger.h"

class TestErrorLoggerDBus: public QObject
{
	Q_OBJECT

private slots:
    void initTestCase();
    void cleanup();

    void canLogMessage();
    void canGetSorted();
    void isNotifiedOnNewItem();
    void isNotifiedWhenListChanges();

private:
   ErrorLoggerDbus *m_eld  = NULL;
   QDBusConnection *m_connection = NULL;
   errorlogger *m_err;
};

#endif /* TESTERRORLOGGERDBUS_H */
