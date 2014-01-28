#include <QtTest/QtTest>
#include "../../../common/browserdbus.h"

class TestBrowserDBus: public QObject
{
	Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testCallUninitialized();
    void testGetTitle();
    void testGetsNotifiedOnUrlChange();
    void testGetsNotifiedOnTitleChange();
    void testGetsNotifiedWhenLinkIsClicked();
    void testGetsNotifiedWhenSelectionChanges();

private:
    BrowserDbus *m_bdb = NULL;
};
