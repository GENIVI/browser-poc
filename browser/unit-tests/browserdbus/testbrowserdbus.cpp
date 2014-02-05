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

void TestBrowserDBus::testGetsNotifiedWhenVisibilityChanges() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (onVisibilityChanged (bool)));
    m_bdb->setVisible(false);
    QVERIFY(spy.wait(1000));
    QVERIFY(spy.last().value(0).toBool() == false);
    m_bdb->setVisible(true);
    QVERIFY(spy.wait(1000));
    QVERIFY(spy.last().value(0).toBool() == true);
}

void TestBrowserDBus::testGetsNotifiedWhenScrollingChanges() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (onScrollPositionChanged (uint,uint)));
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(200);
    QProcess::execute("xdotool mousemove 100 200");
    QProcess::execute("xdotool click 1");
    QProcess::execute("xdotool click 5");
    QVERIFY(spy.wait(10000));
    QProcess::execute("xdotool click 4");
    QVERIFY(spy.wait(10000));
}

void TestBrowserDBus::testCanSetAndGetZoomFactor() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (onZoomFactorChanged (double)));
    m_bdb->loadurl(testFileUrl());

    m_bdb->setZoomFactor(2);
    QVERIFY(m_bdb->getZoomFactor() == 2);
    QVERIFY(spy.wait(10000));
    QVERIFY(spy.last().value(0).toDouble() == 2);

    m_bdb->setZoomFactor(1);
    QVERIFY(m_bdb->getZoomFactor() == 1);
    QVERIFY(spy.wait(10000));
    QVERIFY(spy.last().value(0).toDouble() == 1);
}

void TestBrowserDBus::testCanSetAndGetScrollPosition() {
    uint x = 0, y = 0;
    uint setX = 0, setY = 0;
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (onScrollPositionChanged (uint, uint)));
    m_bdb->loadurl(testFileUrl());

    QTest::qSleep(300);

    setX = 0; setY = 30;
    m_bdb->setScrollPosition(setX, setY);
    m_bdb->getScrollPosition(x,y);
    QVERIFY(y == 30);
    QVERIFY(spy.wait(10000));
    QVERIFY(spy.last().value(1).toUInt() == 30);

    setX = 0; setY = 0;
    m_bdb->setScrollPosition(setX, setY);
    m_bdb->getScrollPosition(x,y);
    QVERIFY(y == 0);
    QVERIFY(spy.wait(10000));
    QVERIFY(spy.last().value(1).toUInt() == 0);
}

void TestBrowserDBus::testCanGeneratePageIcon() {
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QString iconPath = m_bdb->getPageIcon(testFileUrl());
    qDebug() << iconPath;
    QVERIFY(iconPath.compare(QString("")) != 0);
}

void TestBrowserDBus::testCanGetFavicon() {
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QString iconPath = m_bdb->getFavicon(testFileUrl());
    qDebug() << iconPath;
    QVERIFY(iconPath.compare(QString("")) != 0);
}

QTEST_MAIN (TestBrowserDBus);
