#include <QtTest/QtTest>

class TestBrowser: public QObject
{
	Q_OBJECT

private slots:
	void testCanCreate();
	void testCanLoadWebpage();
	void testCanFinishLoadingWebpage();
	void testProgressIncreases();
	void testBack();
	void testForward();
	void testReload();
    void testGetTitle();
    void testGetUrl();
};
