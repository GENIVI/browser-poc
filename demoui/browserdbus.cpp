#include "browserdbus.h"

#include "../browserdefs.h"

#include <QDBusMetaType>


browserdbus::browserdbus(QObject *parent) :
    QObject(parent)
{
    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::BookmarkItem>();
    qDBusRegisterMetaType<conn::brw::BookmarkItemList>();

    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();

    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();

    bookmark = new conn::brw::IBookmarkManager("conn.brw.IBookmarkManager", "/bookmarkmanager",
                                               QDBusConnection::sessionBus(), this);

    userinput = new conn::brw::IUserInput("conn.brw.IUserInput", "/userinput",
                                          QDBusConnection::sessionBus(), this);

    webpagewindow = new conn::brw::IWebPageWindow("conn.brw.IWebPageWindow", "/webpagewindow",
                                                  QDBusConnection::sessionBus(), this);

    browser = new conn::brw::IBrowser("conn.brw.IBrowser", "/browser",
                                      QDBusConnection::sessionBus(), this);
}


void browserdbus::goBack() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = webpagewindow->back();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::goForward() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = webpagewindow->forward();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::reload() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = webpagewindow->reload();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::loadurl(QString url) {
    qDebug() << __PRETTY_FUNCTION__ << url;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = webpagewindow->load(url);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}


void browserdbus::addBookmark(QString bookmarkurl, QString bookmarktitle) {
    qDebug() << __PRETTY_FUNCTION__;

    conn::brw::BookmarkItem test;

    test.i32Uid = 1;
    test.i32Type = 1;
    test.strParentFolderPath = "";
    test.strTitle = bookmarktitle;
    test.strUrl = bookmarkurl;
    test.strIconPath = "";
    test.strThumbnailPath = "";

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->addItem(test);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::getBookmarks() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::BookmarkItemList> reply = bookmark->getItems("", 1, conn::brw::BST_UNSORTED, 1, 2);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::BookmarkItemList ret2 = reply.argumentAt<1>();

        for (int i = 0; i < ret2.size(); ++i) {
            qDebug() << "BookmarkItemList " << ret2.at(i).i32Uid << ret2.at(i).strTitle << ret2.at(i).strUrl << ret2.at(i).strParentFolderPath;
        }
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void browserdbus::test() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, QString, QString> reply = webpagewindow->getCurrentUrlTitle();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        QString ret2 = reply.argumentAt<1>();
        QString ret3 = reply.argumentAt<2>();

        qDebug() << "ERROR_IDS " << ret << ret2 << ret3;

        setName(ret3);
        setBookmarkTitle(ret3);
        }
}
