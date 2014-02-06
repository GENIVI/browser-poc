#include <QSignalSpy>
#include <QDebug>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileInfo>

#include "testbrowser.h"
#include "../../browserview.h"
#include "../../browserconfig.h"

/////////////// Test cases  ///////////////

void TestBrowser::testCanCreate()
{
    BrowserView *bvi = new BrowserView();
    QVERIFY (bvi);
}

void TestBrowser::testCanLoadWebpage()
{
    /*
    FIXME: It seems like the pageLoadStarted signal is not triggered
    correctly
    */
    BrowserView bvi;

    bvi.show();

    QSignalSpy spy (&bvi, SIGNAL(pageLoadStarted()));
    bvi.load("http://www.pelagicore.com");
    QVERIFY (spy.wait(1000));
}

void TestBrowser::testCanFinishLoadingWebpage()
{
    BrowserView bvi;

    bvi.show();

    QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
    bvi.load("http://www.pelagicore.com");
    QVERIFY (spy.wait(10000));
}

void TestBrowser::testProgressIncreases ()
{
    BrowserView bvi;
    QSignalSpy spy (&bvi, SIGNAL(pageLoadProgress(int)));

    bvi.load("http://www.pelagicore.com");
    bvi.show();

    spy.wait(1000);
    float prg = bvi.getProgress();
    QVERIFY(prg > 0);
}

void TestBrowser::testBack ()
{
    BrowserView bvi;
    bvi.show();

    bvi.load("http://www.pelagicore.com");
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(10000));
    }

    bvi.load("http://www.google.com");
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(1000));
    }

    bvi.goBack();
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(1000));
    }

    QVERIFY(bvi.getUrl().contains("pelagicore"));
}

void TestBrowser::testForward ()
{
    BrowserView bvi;
    bvi.show();

    bvi.load("http://www.pelagicore.com");
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(1000));
    }
    QVERIFY(bvi.getUrl().contains("pelagicore"));

    bvi.load("http://www.google.com");
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(1000));
    }

    bvi.goBack();
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(1000));
    }
    bvi.goForward();
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(1000));
    }

    QVERIFY(bvi.getUrl().contains("google"));
}

void TestBrowser::testReload ()
{
    BrowserView bvi;
    bvi.show();

    bvi.load("http://www.pelagicore.com");
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(1000));
    }
    bvi.pageReload();
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        QVERIFY(spy.wait(1000));
    }

    QVERIFY(bvi.getUrl().contains("pelagicore"));
}

//void TestBrowser::testStop () {} //FIXME: How should this be tested..?

void TestBrowser::testGetTitle()
{
    BrowserView bvi;
    QString before = "";
    QString after = "";
    bvi.show();
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        spy.wait(1000);
    }

    before = bvi.getTitle();
    bvi.load("http://www.pelagicore.com");
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        spy.wait(1000);
    }
    after = bvi.getTitle();
    QVERIFY (before.compare(after) != 0);
}

void TestBrowser::testGetUrl()
{
    BrowserView bvi;
    QString before = "";
    QString after = "";
    bvi.show();
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        spy.wait(1000);
    }

    before = bvi.getUrl();
    bvi.load("http://www.pelagicore.com");
    {
        QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
        spy.wait(1000);
    }
    after = bvi.getUrl();
    QVERIFY (before.compare(after) != 0);
}

void TestBrowser::testCanCreateScreenshot() {
    BrowserView bvi;
    bvi.show();
    QString fileName = bvi.createScreenshot("http://pelagicore.com");
    QVERIFY(QFileInfo(fileName).size() > 0);
}

void TestBrowser::testCanGetFavicon () {
    BrowserView bvi;
    bvi.show();
    QString fileName = bvi.getFaviconFilePath("http://www.bmw.com");
    qDebug() << fileName;
    QVERIFY(QFileInfo(fileName).size() > 0);
}

void TestBrowser::testCanSetGetConfigParameter() {
    BrowserConfig conf;
    conf.setValue<int>(BrowserConfig::CONFIG_CACHESIZE, 1337);
    QVERIFY(conf.getValue<int>(BrowserConfig::CONFIG_CACHESIZE) == 1337);

    conf.setValue<QString>(BrowserConfig::CONFIG_CACHESIZE, "1337");
    QVERIFY(conf.getValue<QString>(BrowserConfig::CONFIG_CACHESIZE).compare("1337") == 0);
}

QTEST_MAIN (TestBrowser);
