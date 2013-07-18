#include "browserhelper.h"

#include <QtDBus/QDBusConnection>
//#include <QDBusMetaType>

#include "bookmarkmanager.h"
#include "ibookmarkmanager_adaptor.h"

#include "userinput.h"
#include "iuserinput_adaptor.h"

#include "webpagewindow.h"
#include "iwebpagewindow_adaptor.h"

#include "browser.h"
#include "ibrowser_adaptor.h"

browserhelper::browserhelper(QObject *parent) :
    QObject(parent)
{

//    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
//    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
//    qDBusRegisterMetaType<conn::brw::BookmarkItem>();
//    qDBusRegisterMetaType<conn::brw::BookmarkItemList>();

    bookmarkmanager *bm = new bookmarkmanager();
    new IBookmarkManagerAdaptor(bm);

    QDBusConnection connection = QDBusConnection::sessionBus();
    if(!connection.registerService("conn.brw.IBookmarkManager"))
        qDebug() << "failed register service conn.brw.IBookmarkManager";
    if(!connection.registerObject("/bookmarkmanager", bm))
        qDebug() << "failed register object bookmarkmanager";


//    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
//    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();

    userinput *ui = new userinput();
    new IUserInputAdaptor(ui);

    if(!connection.registerService("conn.brw.IUserInput"))
        qDebug() << "failed register service conn.brw.IUserInput";
    if(!connection.registerObject("/userinput", ui))
        qDebug() << "failed register object userinput";


//    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
//    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();

    webpagewindow *wpw = new webpagewindow();
    new IWebPageWindowAdaptor(wpw);

    if(!connection.registerService("conn.brw.IWebPageWindow"))
        qDebug() << "failed register service conn.brw.IWebPageWindow";
    if(!connection.registerObject("/webpagewindow", wpw))
        qDebug() << "failed register object userinput";


    browser *br = new browser();
    new IBrowserAdaptor(br);

    if(!connection.registerService("conn.brw.IBrowser"))
        qDebug() << "failed register service conn.brw.IBrowser";
    if(!connection.registerObject("/browser", br))
        qDebug() << "failed register object browser";


    connect(wpw, SIGNAL(reloadrequested()), this, SLOT(browserreload()));
    connect(wpw, SIGNAL(stoprequested()), this, SLOT(browserstop()));
    connect(wpw, SIGNAL(backrequested()), this, SLOT(browserback()));
    connect(wpw, SIGNAL(forwardrequested()), this, SLOT(browserforward()));
    connect(wpw, SIGNAL(loadurlrequested(QString)), this, SLOT(browserloadurl(QString)));

}

void browserhelper::browserreload() {
    QMetaObject::invokeMethod(item, "reload");
}

void browserhelper::browserback() {
    QMetaObject::invokeMethod(item, "goBack");
}

void browserhelper::browserforward() {
    QMetaObject::invokeMethod(item, "goForward");
}

void browserhelper::browserstop() {
    QMetaObject::invokeMethod(item, "stop");
}

void browserhelper::browserloadurl(QString url) {
    item->setProperty("url", url);
}
