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

//void TestBrowserDBus::testGetsNotifiedWhenLinkIsHovered() {
//    m_bdb->createPageWindow(1,0,0,800,600);
//    QSignalSpy spy (m_bdb, SIGNAL (linkHovered (QString)));
//    m_bdb->loadurl(testFileUrl());
//
//    QTest::qSleep(200);
//    QProcess::execute("xdotool mousemove 0 0");
//    QProcess::execute("xdotool mousemove 100 100");
//
//    bool success = false;
//    for (int i = 0; i < 10; i++){
//        spy.wait(1000);
//        if (spy.last().value(0).toString().contains("google")) {
//            success = true;
//            break;
//        }
//    }
//
//    QVERIFY(success);
//}

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

void TestBrowserDBus::testOnContentSizeChanged() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (onContentSizeChanged (uint, uint)));
    m_bdb->loadurl(testFileUrl());
    m_bdb->loadurl("http://google.com");
    QVERIFY(spy.wait(1000));
}

void TestBrowserDBus::testOnActionStateChanged() {}
void TestBrowserDBus::testOnFaviconReceived() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QSignalSpy spy (m_bdb, SIGNAL (onFaviconReceived()));
    m_bdb->loadurl(testFileUrl());
    m_bdb->loadurl("http://google.com");
    qDebug() << spy;
    QVERIFY(spy.wait(1000));
}

void TestBrowserDBus::testSelect() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QTest::qSleep(300);
    m_bdb->select();
    QTest::qSleep(300);
    QProcess::execute("xdotool getwindowname `xdotool getwindowfocus`");
}
void TestBrowserDBus::testActivate() {
    m_bdb->createPageWindow(1,0,0,800,600);
    QTest::qSleep(300);
    m_bdb->activate();
    QTest::qSleep(300);
    QProcess::execute("xdotool getwindowname `xdotool getwindowfocus`");
}

void TestBrowserDBus::testConfirmDialog() {
    QSignalSpy spy (m_bdb, SIGNAL(onConfirmDialog(QString)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QProcess::execute("xdotool mousemove 150 500");
    QProcess::execute("xdotool click 1");
    QVERIFY(spy.wait(1000));
    m_bdb->closeConfirmDialog(conn::brw::DR_OK);
}

void TestBrowserDBus::testCancelConfirmDialog() {
    QSignalSpy spy (m_bdb, SIGNAL(onConfirmDialog(QString)));
    QSignalSpy spy2 (m_bdb, SIGNAL(onDialogCanceled(void)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QProcess::execute("xdotool mousemove 150 500");
    QProcess::execute("xdotool click 1");
    QVERIFY(spy.wait(1000));
    m_bdb->closeConfirmDialog(conn::brw::DR_CANCEL);
    QVERIFY(spy2.wait(1000));
}

void TestBrowserDBus::testPromptDialog() {
    QSignalSpy spy (m_bdb, SIGNAL(onPromptDialog(QString,QString)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QProcess::execute("xdotool mousemove 250 500");
    QProcess::execute("xdotool click 1");
    QVERIFY(spy.wait(1000));
    m_bdb->closePromptDialog("Hello!", conn::brw::DR_OK);
}

void TestBrowserDBus::testCancelPromptDialog() {
    QSignalSpy spy (m_bdb, SIGNAL(onPromptDialog(QString,QString)));
    QSignalSpy spy2 (m_bdb, SIGNAL(onDialogCanceled(void)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QProcess::execute("xdotool mousemove 250 500");
    QProcess::execute("xdotool click 1");
    QVERIFY(spy.wait(1000));
    m_bdb->closePromptDialog("Hello!", conn::brw::DR_CANCEL);
    QVERIFY(spy2.wait(1000));
}

void TestBrowserDBus::testAlertDialog() {
    QSignalSpy spy (m_bdb, SIGNAL(onAlertDialog(QString)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QProcess::execute("xdotool mousemove 50 500");
    QProcess::execute("xdotool click 1");
    QVERIFY(spy.wait(1000));
    m_bdb->closeAlertDialog();
}

void TestBrowserDBus::testGetPrevEnteredValues() {
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QProcess::execute("xdotool mousemove 200 375");
    QProcess::execute("xdotool click 1");
    QTest::qSleep(300);
    m_bdb->inputText(conn::brw::DR_OK, "Hello world");
    QTest::qSleep(300);
    QStringList list = m_bdb->getPrevEnteredValues("input", "", conn::brw::IET_TEXT);
    QVERIFY(list.contains("Hello world"));
}

void TestBrowserDBus::testGetsNotifiedWhenSelectIsSelected() {
    QSignalSpy spy (m_bdb, SIGNAL(onSelect(const QString &, const conn::brw::SelectableOptionList &, bool)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QProcess::execute("xdotool mousemove 320 375");
    QProcess::execute("xdotool click 1");
    QTest::qSleep(300);
    QProcess::execute("xdotool click 1");
    QVERIFY(spy.wait(1000));
    conn::brw::SelectableOptionList options = spy.takeFirst().at(1).value<conn::brw::SelectableOptionList>();
    for (int i = 0; i < options.size(); i++) {
        qDebug() << options.at(i).strValue;
    }
}

void TestBrowserDBus::testGetsNotifiedOnAuthDialog() {
    QSignalSpy spy (m_bdb, SIGNAL(onAuthenticationDialog(const conn::brw::AuthenticationData&)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl("http://www.httpwatch.com/httpgallery/authentication/authenticatedimage/default.aspx");
    QVERIFY(spy.wait(1000));
}

void TestBrowserDBus::testCanCloseAuthDialog() {
    QSignalSpy spy (m_bdb, SIGNAL(onAuthenticationDialog(const conn::brw::AuthenticationData&)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl("http://www.httpwatch.com/httpgallery/authentication/authenticatedimage/default.aspx");
    QVERIFY(spy.wait(1000));

    conn::brw::AuthenticationData d;
    d.strUserName = "httpwatch";
    d.strPassword = QString(qrand());
    qDebug() << ": user" << d.strUserName << "password:" << d.strPassword;
    m_bdb->closeAuthenticationDialog(conn::brw::DR_OK, d);
}

void TestBrowserDBus::testGetsNotifiedOnBadSSL() {
    QSignalSpy spy (m_bdb, SIGNAL(onSslErrorDialog(const conn::brw::SslError&)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl("https://tv.eurosport.com/");
    QVERIFY(spy.wait(1000));
}

void TestBrowserDBus::testCanCloseSslDialog() {
    QSignalSpy spy (m_bdb, SIGNAL(onSslErrorDialog(const conn::brw::SslError&)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl("https://tv.eurosport.com/");
    QVERIFY(spy.wait(1000));
    conn::brw::SslError error = spy.takeFirst().at(0).value<conn::brw::SslError>();
    qDebug() << "SSL error is:" << error.strErrorMessage << ". code:" << error.sslError;

    m_bdb->closeSslErrorDialog(conn::brw::DR_OK, true);
}

void TestBrowserDBus::testCanCancelSSL() {
    QSignalSpy spy (m_bdb, SIGNAL(onSslErrorDialog(const conn::brw::SslError&)));
    QSignalSpy spy2 (m_bdb, SIGNAL(onSslErrorDialogCancel(const conn::brw::SslError&)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl("https://tv.eurosport.com/");
    QVERIFY(spy.wait(1000));
    m_bdb->closeSslErrorDialog(conn::brw::DR_CANCEL, false);
    QVERIFY(spy2.wait());
}

void TestBrowserDBus::testCanCancelAuth() {
    QSignalSpy spy (m_bdb, SIGNAL(onAuthenticationDialog(const conn::brw::AuthenticationData&)));
    QSignalSpy spy2 (m_bdb, SIGNAL(onAuthenticationDialogCancel(const conn::brw::AuthenticationData&)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl("http://www.httpwatch.com/httpgallery/authentication/authenticatedimage/default.aspx");
    QVERIFY(spy.wait(1000));

    conn::brw::AuthenticationData d;
    m_bdb->closeAuthenticationDialog(conn::brw::DR_CANCEL, d);
    QVERIFY(spy2.wait(1000));
}

void TestBrowserDBus::testCanSelectOptionsInSelectList() {
    QSignalSpy spy (m_bdb, SIGNAL(onSelect(const QString &, const conn::brw::SelectableOptionList &, bool)));
    m_bdb->createPageWindow(1,0,0,800,600);
    m_bdb->loadurl(testFileUrl());
    QTest::qSleep(300);
    QProcess::execute("xdotool mousemove 320 375");
    QProcess::execute("xdotool click 1");
    QTest::qSleep(300);
    QProcess::execute("xdotool click 1");
    QVERIFY(spy.wait(1000));
    conn::brw::SelectableOptionList options = spy.takeFirst().at(1).value<conn::brw::SelectableOptionList>();
    conn::brw::SelectableOption newOption = options.at(0);
    conn::brw::SelectableOption newOption2 = options.at(1);
    newOption.bSelected = true;
    newOption2.bSelected = true;
    options.replace(0, newOption);
    options.replace(1, newOption2);
    
    m_bdb->selectOption(options);
}

QTEST_MAIN (TestBrowserDBus);
