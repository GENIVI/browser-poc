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
#include <QDBusConnection>
#include <QDateTime>

#include "../../../common/errorloggerdbus.h"
#include "../../../common/browserdefs.h"

#include "testerrorloggerdbus.h"
#include "ierrorlogger_interface.h"
#include "ierrorlogger_adaptor.h"
#include "../../errorlogger.h"

void TestErrorLoggerDBus::initTestCase() {
    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::BookmarkItem>();
    qDBusRegisterMetaType<conn::brw::BookmarkItemList>();
    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();
    qDBusRegisterMetaType<conn::brw::Rect>();
    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();
    qDBusRegisterMetaType<conn::brw::BrowserActions>();
    qDBusRegisterMetaType<conn::brw::OBJECT_HANDLE>();
    qDBusRegisterMetaType<conn::brw::ObjectHandleList>();
    qDBusRegisterMetaType<conn::brw::CACHE_POLICY>();

    m_connection = new QDBusConnection(QDBusConnection::sessionBus());
    if(!m_connection->isConnected()) {
        qDebug() << "failed to connect to dbus";
        exit(1);
    }

    QString *dbusservicename = new QString("genivi.poc.browser1");
    qDebug() << *dbusservicename;

//    if(!m_connection->registerService(*dbusservicename)) {
//        qDebug() << "failed register service " << *dbusservicename;
//        exit(1);
//    }
//
    m_err = errorlogger::instance();
//    new IErrorLoggerAdaptor(m_err);
//    if(!m_connection->registerObject("/Browser/IErrorLogger", m_err))
//        QFAIL("failed register object IErrorLogger");

    m_eld = new ErrorLoggerDbus();
    m_eld->connectdbussession("1");
}
void TestErrorLoggerDBus::cleanup()
{
    m_err->clearErrors();
}

void TestErrorLoggerDBus::canLogMessage()
{
    qlonglong date = QDateTime::currentDateTime().toTime_t();
    errorlogger* el = errorlogger::instance();
    el->logError("Error!");
    el->logError("Error2!");
//    QVERIFY(m_eld->getItemsCount(date - 10, date + 10) == 2);
    conn::brw::ErrorItemList items = m_eld->getItems(date - 10,
        date + 10, conn::brw::EST_DATE_DESCENDING, 0, 100);
    QVERIFY(items.size() == 2);
}

void TestErrorLoggerDBus::canGetSorted()
{
    qlonglong date = QDateTime::currentDateTime().toTime_t();
    errorlogger* el = errorlogger::instance();
    el->logError("Error!");
    QTest::qSleep(1000);
    el->logError("Error2!");
    conn::brw::ErrorItemList items = m_eld->getItems(date - 10,
        date + 10, conn::brw::EST_DATE_ASCENDING, 0, 100);
    qDebug() << items.size();
    qDebug() << items.at(0).strDescription;
    qDebug() << items.at(1).strDescription;
    QVERIFY(items.at(0).strDescription.compare("Error!") == 0);
    QVERIFY(items.at(1).strDescription.compare("Error2!") == 0);
}

void TestErrorLoggerDBus::isNotifiedOnNewItem()
{
    QSignalSpy spy (m_eld, SIGNAL(onNewErrorItem(conn::brw::ErrorItem)));
    errorlogger::instance()->logError("Error!");
    QVERIFY (spy.wait(1000));
}

void TestErrorLoggerDBus::isNotifiedWhenListChanges()
{
    QSignalSpy spy (m_eld, SIGNAL(onErrorListChanged(void)));
    errorlogger::instance()->clearErrors();
    QVERIFY (spy.wait(1000));
}
QTEST_MAIN (TestErrorLoggerDBus);
