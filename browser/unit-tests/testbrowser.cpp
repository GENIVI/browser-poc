#include <QSignalSpy>
#include <QDebug>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "testbrowser.h"
#include "../browserviewportitem.h"

/////////////// Test cases  ///////////////

void TestBrowser::testCanCreate()
{
	BrowserViewportItem *bvi = new BrowserViewportItem();
	QVERIFY (bvi);
}

void TestBrowser::testCanLoadWebpage()
{
	/*
	FIXME: It seems like the pageLoadStarted signal is not triggered
	correctly
	*/
	BrowserViewportItem bvi;

	bvi.show();

	QSignalSpy spy (&bvi, SIGNAL(pageLoadStarted()));
	bvi.load("http://www.pelagicore.com");
	QVERIFY (spy.wait(1000));
}

void TestBrowser::testCanFinishLoadingWebpage()
{
	BrowserViewportItem bvi;

	bvi.show();

	QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
	bvi.load("http://www.pelagicore.com");
	QVERIFY (spy.wait(10000));
}

void TestBrowser::testProgressIncreases ()
{
	BrowserViewportItem bvi;
	QSignalSpy spy (&bvi, SIGNAL(pageLoadProgress(int)));

	bvi.load("http://www.pelagicore.com");
	bvi.show();

	spy.wait(1000);
	float prg = bvi.getProgress();
	QVERIFY(prg > 0);
}

void TestBrowser::testBack ()
{
	BrowserViewportItem bvi;
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

	QVERIFY(bvi.getURL().contains("pelagicore"));
}

void TestBrowser::testForward ()
{
	BrowserViewportItem bvi;
	bvi.show();

	bvi.load("http://www.pelagicore.com");
	{
		QSignalSpy spy (&bvi, SIGNAL(pageLoadFinished(bool)));
		QVERIFY(spy.wait(1000));
	}
	QVERIFY(bvi.getURL().contains("pelagicore"));

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

	QVERIFY(bvi.getURL().contains("google"));
}

void TestBrowser::testReload ()
{
	BrowserViewportItem bvi;
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

	QVERIFY(bvi.getURL().contains("pelagicore"));
}

QTEST_MAIN (TestBrowser);
