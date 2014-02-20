/**
 * Copyright (C) 2013, Pelagicore
 *
 * Author: Marcel Schuette <marcel.schuette@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <QDBusMetaType>
#include <QtQml>

#include "browserdbus.h"

#include "../common/browserdefs.h"

BrowserDbus::BrowserDbus(QObject *parent) :
    QObject(parent), bookmark(NULL),
    userinput(NULL), webpagewindow(NULL), actualtab(NULL),
    actualuserinput(NULL), networkmanager(NULL), browser(NULL), 
    m_instanceId("1"), m_isconnected(false), dbusservicename(NULL)
{
    qDebug() << __PRETTY_FUNCTION__;

    registertypes();
}

void BrowserDbus::registertypes() {
    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();
    qDBusRegisterMetaType<conn::brw::BookmarkItem>();
    qDBusRegisterMetaType<conn::brw::BookmarkItemList>();
    qDBusRegisterMetaType<conn::brw::DIALOG_RESULT>();
    qDBusRegisterMetaType<conn::brw::INPUT_ELEMENT_TYPE>();
    qDBusRegisterMetaType<conn::brw::Rect>();
    qDBusRegisterMetaType<conn::brw::SCROLL_DIRECTION>();
    qDBusRegisterMetaType<conn::brw::SCROLL_TYPE>();
    qDBusRegisterMetaType<conn::brw::BrowserActions>();
    qDBusRegisterMetaType<conn::brw::OBJECT_HANDLE>();
    qDBusRegisterMetaType<conn::brw::ObjectHandleList>();
    qDBusRegisterMetaType<conn::brw::AuthenticationData>();
    qDBusRegisterMetaType<conn::brw::SSL_ERROR>();
    qDBusRegisterMetaType<conn::brw::SslError>();
    qDBusRegisterMetaType<conn::brw::SelectableOptionList>();
    qDBusRegisterMetaType<conn::brw::SelectableOption>();
}

void BrowserDbus::connectdbussession(QString id) {
    qDebug() << __PRETTY_FUNCTION__ << id;

    m_instanceId = id;

    dbusservicename = new QString("genivi.poc.browser" + m_instanceId);

    browser = new conn::brw::IBrowser(*dbusservicename, "/Browser/IBrowser",
                                      QDBusConnection::sessionBus(), this);
    m_isconnected = true;
    if(!browser->isValid()) {
        qDebug() << "failed create object /Browser/IBrowser";
        m_isconnected = false;
    }
    emit connectedChanged();

    connect(browser, SIGNAL(onPageWindowDestroyed(qlonglong)), this, SLOT(PageWindowDestroyed(qlonglong)));
    connect(browser, SIGNAL(onPageWindowCreated(qlonglong,conn::brw::ERROR_IDS)), this, SLOT(PageWindowCreated(qlonglong,conn::brw::ERROR_IDS)));

    bookmark = new conn::brw::IBookmarkManager(*dbusservicename, "/Browser/IBookmarkManager",
                                               QDBusConnection::sessionBus(), this);
    if(!bookmark->isValid())
        qDebug() << "failed create object /Browser/IBookmarkManager";
}

void BrowserDbus::selectTab(int tabnumber) {
    qDebug() << __PRETTY_FUNCTION__ << tabnumber;

    if(handlelist.length() >= tabnumber) {
        actualtab = webpagehash.value(handlelist.at(tabnumber-1));
        actualuserinput = inputhash.value(handlelist.at(tabnumber-1));
    }
}

// IBookmarkManager
void BrowserDbus::addBookmark(int type, QString folder, QString title, QString url, QString iconpath, QString thumbnailpath) {
    qDebug() << __PRETTY_FUNCTION__ << type << folder << title << url << iconpath << thumbnailpath;

    conn::brw::BookmarkItem tmpbookmark;
    tmpbookmark.i32Uid = 0;
    tmpbookmark.i32Type = type;
    tmpbookmark.strParentFolderPath = folder;
    tmpbookmark.strTitle = title;
    tmpbookmark.strUrl = url;
    tmpbookmark.strIconPath = iconpath;
    tmpbookmark.strThumbnailPath = thumbnailpath;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->addItem(tmpbookmark);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::getBookmarks(QString folder, int type, conn::brw::BOOKMARK_SORT_TYPE sorting, int start, int count) {
    qDebug() << __PRETTY_FUNCTION__ << folder << type << sorting << start << count;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::BookmarkItemList> reply = bookmark->getItems(folder, type, sorting, start, count);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::BookmarkItemList bookmarklist = reply.argumentAt<1>();

        m_bookmarkList.clear();
        for (int i = 0; i < bookmarklist.size(); ++i) {
            qDebug() << "BookmarkItemList" << bookmarklist.at(i).i32Uid << bookmarklist.at(i).strTitle << bookmarklist.at(i).strUrl << bookmarklist.at(i).strParentFolderPath;
            m_bookmarkList.append(new Bookmark(bookmarklist.at(i).strTitle, bookmarklist.at(i).strUrl, bookmarklist.at(i).i32Uid));
            emit bookmarkListChanged();
        }

        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::deleteAllBookmarks(int type) {
    qDebug() << __PRETTY_FUNCTION__ << type;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteAllItems(type);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        m_bookmarkList.clear();
        emit bookmarkListChanged();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::deleteBookmark(int uid) {
    qDebug() << __PRETTY_FUNCTION__ << uid;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteItem(uid);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }

    for(int i = 0; i < m_bookmarkList.size(); ++i) {
        if(uid == m_bookmarkList.at(i)->uid())
            m_bookmarkList.removeAt(i);
    }
    emit bookmarkListChanged();
}

// IBrowser
void BrowserDbus::createPageWindow(int deviceid, int x, int y, int width, int height) {
    qDebug() << __PRETTY_FUNCTION__ << x << y << width << height;

    conn::brw::Rect *rect = new conn::brw::Rect();
    rect->i32X = x;
    rect->i32Y = y;
    rect->i32Width = width;
    rect->i32Height = height;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::OBJECT_HANDLE> reply = browser->createPageWindow(deviceid, *rect);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::OBJECT_HANDLE handle = reply.argumentAt<1>();

        qDebug() << "ERROR_IDS " << ret << handle;

        QString *webpagewindowservice = new QString("/Browser/IWebPageWindow" + QString::number(handle));
        webpagewindow = new conn::brw::IWebPageWindow(*dbusservicename, *webpagewindowservice,
                                                      QDBusConnection::sessionBus(), this);

        webpagehash.insert(handle, webpagewindow);
        handlelist.append(handle);
        actualtab = webpagewindow;

        if(!actualtab->isValid())
            qDebug() << "failed create object /Browser/IWebPageWindow*";

        connect(actualtab, SIGNAL(onLoadStarted()),                  this, SLOT(pageloadingstarted()));
        connect(actualtab, SIGNAL(onLoadFinished(bool)),             this, SLOT(pageloadingfinished(bool)));
        connect(actualtab, SIGNAL(onLoadProgress(int)),              this, SLOT(pageloadingprogress(int)));
        connect(actualtab, SIGNAL(onClose()),                        this, SLOT(WindowClosed()));
        connect(actualtab, SIGNAL(onUrlChanged(QString)),            this, SIGNAL(urlChanged(QString)));
        connect(actualtab, SIGNAL(onTitleChanged(QString)),          this, SIGNAL(titleChanged(QString)));
        connect(actualtab, SIGNAL(onLinkClicked(QString)),           this, SIGNAL(linkClicked(QString)));
        connect(actualtab, SIGNAL(onSelectionChanged(void)),         this, SIGNAL(selectionChanged(void)));
        connect(actualtab, SIGNAL(onStatusTextChanged(QString)),     this, SIGNAL(onStatusTextChanged(QString)));
        connect(actualtab, SIGNAL(onVisibilityChanged(bool)),        this, SIGNAL(onVisibilityChanged(bool)));
        connect(actualtab, SIGNAL(onScrollPositionChanged(uint,uint)), this, SIGNAL(onScrollPositionChanged(uint,uint)));
        connect(actualtab, SIGNAL(onZoomFactorChanged(double)),      this, SIGNAL(onZoomFactorChanged(double)));
        connect(actualtab, SIGNAL(onLinkHovered(QString)),           this, SIGNAL(linkHovered(QString)));
        connect(actualtab, SIGNAL(onActionStateChanged(uint)),       this, SIGNAL(onActionStateChanged(uint)));
        connect(actualtab, SIGNAL(onContentSizeChanged(uint, uint)), this, SIGNAL(onContentSizeChanged(uint,uint)));
        connect(actualtab, SIGNAL(onFaviconReceived()),              this, SIGNAL(onFaviconReceived()));

        QString *userinputservice = new QString(*webpagewindowservice + "/IUserInput");

        userinput = new conn::brw::IUserInput(*dbusservicename, *userinputservice,
                                              QDBusConnection::sessionBus(), this);
        inputhash.insert(handle, userinput);
        actualuserinput = userinput;

        connect(actualuserinput, SIGNAL(onAlertDialog(QString)),         this, SIGNAL(onAlertDialog(QString)));
        connect(actualuserinput, SIGNAL(onConfirmDialog(QString)),       this, SIGNAL(onConfirmDialog(QString)));
        connect(actualuserinput, SIGNAL(onPromptDialog(QString,QString)),this, SIGNAL(onPromptDialog(QString,QString)));
        connect(actualuserinput, SIGNAL(onDialogCanceled(void)),         this, SIGNAL(onDialogCanceled()));
        connect(actualuserinput, SIGNAL(onSelect(const QString &, const conn::brw::SelectableOptionList &, bool)),
                this,            SIGNAL(onSelect(const QString &, const conn::brw::SelectableOptionList &, bool)));

        if(!actualuserinput->isValid())
            qDebug() << "failed create object /Browser/IWebPageWindow*/IUserInput";

        connect(actualuserinput, SIGNAL(onInputText(QString,QString,conn::brw::INPUT_ELEMENT_TYPE,int,int,int,int)), this, SLOT(InputTextReceived(QString,QString,conn::brw::INPUT_ELEMENT_TYPE,int,int,int,int)));

        QString *networkmanagerservice = new QString(*webpagewindowservice + "/INetworkManager");

        networkmanager = new conn::brw::INetworkManager(*dbusservicename, *networkmanagerservice,
                                              QDBusConnection::sessionBus(), this);

        connect(networkmanager, SIGNAL(onAuthenticationDialog(const conn::brw::AuthenticationData&)),
                this, SIGNAL(onAuthenticationDialog(const conn::brw::AuthenticationData&)));
        connect(networkmanager, SIGNAL(onSslErrorDialog(const conn::brw::SslError&)),
                this, SIGNAL(onSslErrorDialog(const conn::brw::SslError&)));
        connect(networkmanager, SIGNAL(onSslErrorDialogCancel(const conn::brw::SslError&)),
                this, SIGNAL(onSslErrorDialogCancel(const conn::brw::SslError&)));
        connect(networkmanager, SIGNAL(onAuthenticationDialogCancel(const conn::brw::AuthenticationData&)),
                this, SIGNAL(onAuthenticationDialogCancel(const conn::brw::AuthenticationData&)));
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::destroyPageWindow(qlonglong windowhandle) {
    qDebug() << __PRETTY_FUNCTION__ << windowhandle;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = browser->destroyPageWindow(windowhandle);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();

        webpagehash.remove(windowhandle);
        inputhash.remove(windowhandle);
        handlelist.removeOne(windowhandle);

        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }

}

void BrowserDbus::getPageWindows() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::ObjectHandleList> reply = browser->getPageWindows();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::ObjectHandleList list = reply.argumentAt<1>();

        qDebug() << "ERROR_IDS " << ret;
        for(int i = 0; i < list.size(); i++)
            qDebug() << list.at(i);
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::PageWindowDestroyed(qlonglong handle) {
    qDebug() << __PRETTY_FUNCTION__ << handle;
}

void BrowserDbus::PageWindowCreated(qlonglong handle, conn::brw::ERROR_IDS result) {
        qDebug() << __PRETTY_FUNCTION__ << handle << result;
}

// IUserInput
void BrowserDbus::inputText(conn::brw::DIALOG_RESULT a_eResult, QString a_strInputValue) {
    qDebug() << __PRETTY_FUNCTION__ << a_eResult << a_strInputValue;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualuserinput->inputText(a_eResult, a_strInputValue);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();

        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::closeAlertDialog()
{
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualuserinput->closeAlertDialog();

    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();

        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::closeConfirmDialog(conn::brw::DIALOG_RESULT d)
{
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualuserinput->closeConfirmDialog(d);

    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();

        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::closePromptDialog(QString s, conn::brw::DIALOG_RESULT d)
{
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualuserinput->closePromptDialog(s,d);

    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();

        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::InputTextReceived(QString a_strInputName, QString a_strDefaultInputValue, conn::brw::INPUT_ELEMENT_TYPE a_i32InputValueType, int a_s32MaxLength, int a_s32Max, int a_s32Min, int a_s32Step) {
    qDebug() << __PRETTY_FUNCTION__ << a_strInputName << a_strDefaultInputValue << a_i32InputValueType << a_s32MaxLength << a_s32Max << a_s32Min << a_s32Step;
}

// IWebPageWindow
void BrowserDbus::getBrowserActionState() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::BrowserActions> reply = actualtab->getBrowserActionsState();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::BrowserActions actions = reply.argumentAt<1>();

        qDebug() << "ERROR_IDS " << ret << actions.u8Back << actions.u8Forward <<
                    actions.u8Reload << actions.u8Stop << actions.u8LoadUrl << actions.u8Select;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::getContentSize() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, uint, uint> reply = actualtab->getContentSize();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        uint width = reply.argumentAt<1>();
        uint height = reply.argumentAt<2>();

        qDebug() << "ERROR_IDS " << ret << width << height;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::getGeometry() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS, conn::brw::Rect> reply = actualtab->getGeometry();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        conn::brw::Rect rect = reply.argumentAt<1>();

        qDebug() << "ERROR_IDS " << ret << rect.i32X << rect.i32X << rect.i32Width << rect.i32Height;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::setGeometry(int x, int y, int width, int height) {
    qDebug() << __PRETTY_FUNCTION__ << x << y << width << height;

    conn::brw::Rect *rect = new conn::brw::Rect();
    rect->i32X = x;
    rect->i32Y = y;
    rect->i32Width = width;
    rect->i32Height = height;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->setGeometry(*rect);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();

        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::setVisible(bool visible) {
    qDebug() << __PRETTY_FUNCTION__ << visible;
    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->setVisible(visible);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::getVisible() {
    qDebug() << __PRETTY_FUNCTION__;
    QDBusPendingReply<bool> reply = actualtab->getVisible();
    reply.waitForFinished();
    if(reply.isValid()) {
        bool ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::pageloadingstarted() {
    qDebug() << __PRETTY_FUNCTION__;
    setPageLoading(true);
    emit pageloadingChanged();
}

void BrowserDbus::pageloadingfinished(bool success) {
    qDebug() << __PRETTY_FUNCTION__ << success;
    if(success) {
        getUrl();
        getTitle();
        qDebug() << __PRETTY_FUNCTION__ << url() << title();
    }
    setPageLoading(false);
    emit pageloadingChanged();
}

void BrowserDbus::pageloadingprogress(int progress) {
    qDebug() << __PRETTY_FUNCTION__ << progress << pageloading();
    setProgress(progress);
    emit progressChanged();
}

void BrowserDbus::goDown(conn::brw::SCROLL_TYPE type) {
    qDebug() << __PRETTY_FUNCTION__ << type;

    scrollpage(conn::brw::SD_BOTTOM, type);
}
void BrowserDbus::goUp(conn::brw::SCROLL_TYPE type) {
    qDebug() << __PRETTY_FUNCTION__ << type;

    scrollpage(conn::brw::SD_TOP, type);
}
void BrowserDbus::goLeft(conn::brw::SCROLL_TYPE type) {
    qDebug() << __PRETTY_FUNCTION__ << type;

    scrollpage(conn::brw::SD_LEFT, type);
}
void BrowserDbus::goRight(conn::brw::SCROLL_TYPE type) {
    qDebug() << __PRETTY_FUNCTION__ << type;

    scrollpage(conn::brw::SD_RIGHT, type);
}

void BrowserDbus::scrollpage(conn::brw::SCROLL_DIRECTION direction, conn::brw::SCROLL_TYPE type) {
    qDebug() << __PRETTY_FUNCTION__ << direction;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->scroll(direction, type);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::goBack() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->back();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::goForward() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->forward();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::reload() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->reload();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::stop() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->stop();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::loadurl(QString url) {
    qDebug() << __PRETTY_FUNCTION__ << url;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->load(url);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::WindowClosed() {
    qDebug() << __PRETTY_FUNCTION__;
}

QString BrowserDbus::getUrl() {
    qDebug() << __PRETTY_FUNCTION__;
    if (!actualtab) {
        qDebug() << "No browser window present";
        return "";
    }

    QDBusPendingReply<QString> reply = actualtab->getUrl();
    reply.waitForFinished();
    if (reply.isValid()) {
        setUrl(reply.value());
        qDebug() << __PRETTY_FUNCTION__ << url();
    }
    return url();
}

QString BrowserDbus::getTitle() {
    qDebug() << __PRETTY_FUNCTION__;
    if (!actualtab) {
        qDebug() << "No browser window present";
        return "";
    }

    QDBusPendingReply<QString> reply = actualtab->getTitle();
    reply.waitForFinished();
    if (reply.isValid()) {
        setTitle(reply.value());
        qDebug() << __PRETTY_FUNCTION__ << title();
    }
    return title();
}

void BrowserDbus::setZoomFactor(double factor) {
    qDebug() << __PRETTY_FUNCTION__ << factor;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->setZoomFactor(factor);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

double BrowserDbus::getZoomFactor() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<double> reply = actualtab->getZoomFactor();
    reply.waitForFinished();
    if(reply.isValid()) {
        double ret = reply.value();
        return ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
        return 0;
    }
}

void BrowserDbus::getScrollPosition(uint &x, uint &y) {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusReply<conn::brw::ERROR_IDS> reply = actualtab->getScrollPosition(x,y);
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::setScrollPosition(uint &x, uint &y) {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = actualtab->setScrollPosition(x,y);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

QString BrowserDbus::getPageIcon(QString iconPath) {
    qDebug() << __PRETTY_FUNCTION__;
    QString iconFilePath;

    QDBusReply<conn::brw::ERROR_IDS> reply =
                       actualtab->getPageIcon(iconPath,iconFilePath);
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
    return iconFilePath;
}

QString BrowserDbus::getFavicon(QString iconPath) {
    qDebug() << __PRETTY_FUNCTION__;
    QString iconFilePath;

    QDBusReply<conn::brw::ERROR_IDS> reply =
                       actualtab->getFavicon(iconPath,iconFilePath);
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
    return iconFilePath;
}

void BrowserDbus::activate() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusReply<conn::brw::ERROR_IDS> reply = actualtab->activate();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}
void BrowserDbus::select() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusReply<conn::brw::ERROR_IDS> reply = actualtab->select();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

QStringList BrowserDbus::getPrevEnteredValues(QString name, QString value, conn::brw::INPUT_ELEMENT_TYPE type)
{
    qDebug() << __PRETTY_FUNCTION__;
    QStringList list;

    QDBusReply<conn::brw::ERROR_IDS> reply = actualuserinput->getPrevEnteredValues(name, value, type, list);
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
    return list;
}

void BrowserDbus::closeAuthenticationDialog(conn::brw::DIALOG_RESULT r, const conn::brw::AuthenticationData& d)
{
    qDebug() << __PRETTY_FUNCTION__;
    QStringList list;

    QDBusReply<conn::brw::ERROR_IDS> reply = networkmanager->closeAuthenticationDialog(r,d);
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void BrowserDbus::closeSslErrorDialog(conn::brw::DIALOG_RESULT r, bool b)
{
    qDebug() << __PRETTY_FUNCTION__;
    QStringList list;

    QDBusReply<conn::brw::ERROR_IDS> reply = networkmanager->closeSslErrorDialog(r,b);
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "ERROR_IDS " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}
