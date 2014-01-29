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

#include "testbrowserdbus.h"

//////////// Setup & teardown  /////////////

void TestBrowserDBus::initTestCase () {
    m_bdb = new BrowserDbus (this);
    m_bdb->connectdbussession("1");
    m_pagefile = new QTemporaryFile("XXXXXX.html");
    m_pagefile->open();
    m_pagefile->write(WebPageGenerator::testPageContents());
    m_pagefile->flush();
}

void TestBrowserDBus::cleanupTestCase() {
    m_pagefile->remove();
    delete m_pagefile;
    delete m_bdb;
}

/////////////// Test cases  ///////////////

/* Verify that our dbus-functions give sane values even when the PageWindow has
 * not yet been initialized */
void TestBrowserDBus::testCallUninitialized() {
    QVERIFY(m_bdb->connected());
    QVERIFY (m_bdb->getUrl().compare("") == 0);
    QVERIFY (m_bdb->getTitle().compare("") == 0);
}

void TestBrowserDBus::testGetTitle() {
    QSignalSpy spy (m_bdb, SIGNAL (pageloadingChanged(void)));
    m_bdb->createPageWindow(1,0,0,10,10);
    spy.wait(1000);
    QVERIFY (m_bdb->getTitle().compare("") != 0);
}

void TestBrowserDBus::testGetsNotifiedOnUrlChange() {
    m_bdb->createPageWindow(1,0,0,10,10);
    QSignalSpy spy (m_bdb, SIGNAL (urlChanged (QString)));
    m_bdb->loadurl(testFileUrl());

    spy.wait(1000);
    QVERIFY(spy.value(0).value(0).toString().contains(testFileUrl()));
}

void TestBrowserDBus::testGetsNotifiedOnTitleChange() {
    m_bdb->createPageWindow(1,0,0,10,10);
    QSignalSpy spy (m_bdb, SIGNAL (titleChanged (QString)));
    m_bdb->loadurl(testFileUrl());

    spy.wait(10000);
    qDebug() << spy.value(0).value(0).toString();
    QVERIFY(spy.value(0).value(0).toString().contains("Browser PoC"));
}

void TestBrowserDBus::testGetsNotifiedWhenLinkIsClicked() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (linkClicked (QString)));
    m_bdb->loadurl(testFileUrl());

    QTest::qSleep(200);
    QProcess::execute("xdotool mousemove 100 100");
    QProcess::execute("xdotool click 1");
    QVERIFY(spy.wait(10000));
}

void TestBrowserDBus::testGetsNotifiedWhenSelectionChanges() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (selectionChanged ()));
    m_bdb->loadurl(testFileUrl());

    QTest::qSleep(200);
    QProcess::execute("xdotool mousemove 100 200");
    QProcess::execute("xdotool mousedown 1");
    QProcess::execute("xdotool mousemove 100 300");
    QProcess::execute("xdotool mouseup 1");
    QVERIFY(spy.wait(10000));
}

void TestBrowserDBus::testGetsNotifiedWhenStatusBarChanges() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (onStatusTextChanged (QString)));
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(200);
    QProcess::execute("xdotool mousemove 100 400");
    QProcess::execute("xdotool click 1");

    bool success = false;
    for (int i = 0; i < 10; i++){
        spy.wait(1000);
        if (spy.last().value(0).toString().contains("browser-poc")) {
            success = true;
            break;
        }
    }

    QVERIFY(success);
}

QTEST_MAIN (TestBrowserDBus);
