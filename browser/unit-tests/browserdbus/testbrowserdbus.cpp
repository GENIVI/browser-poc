#include <QSignalSpy>
#include <QDebug>

#include "testbrowserdbus.h"
#include "../../../common/browserdbus.h"


//////////// Setup & teardown  /////////////

void TestBrowserDBus::initTestCase () {
    m_bdb = new BrowserDbus (this);
    m_bdb->connectdbussession("1");
}

void TestBrowserDBus::cleanupTestCase() {
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
    m_bdb->loadurl("http://www.google.com");

    spy.wait(1000);
    QVERIFY(spy.value(0).value(0).toString().contains("google"));
}

void TestBrowserDBus::testGetsNotifiedOnTitleChange() {
    m_bdb->createPageWindow(1,0,0,10,10);
    QSignalSpy spy (m_bdb, SIGNAL (titleChanged (QString)));
    m_bdb->loadurl("http://www.google.com");

    spy.wait(10000);
    qDebug() << spy.value(0).value(0).toString();
    QVERIFY(spy.value(0).value(0).toString().contains("Google"));
}

QTEST_MAIN (TestBrowserDBus);
