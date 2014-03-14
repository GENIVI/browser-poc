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

#include <QDebug>
#include <QDBusConnection>
#include <QFile>

#include "browser.h"
#include "browserview.h"
#include "userinput.h"
#include "networkmanager.h"
#include "iwebpagewindow_adaptor.h"
#include "iuserinput_adaptor.h"

browser::browser(cachemanager *manager, networkmanager *nm, QObject *parent) :
    QObject(parent), m_cacheManager (manager), m_networkManager(nm)
{
    qDebug() << __PRETTY_FUNCTION__;
}

conn::brw::ERROR_IDS browser::createPageWindow(int a_eDeviceId, const conn::brw::Rect & a_oGeometry, conn::brw::OBJECT_HANDLE &a_hPageWindowHandle) {
    qDebug() << __PRETTY_FUNCTION__;

    Q_UNUSED(a_eDeviceId);

    userinput *m_userInput = new userinput();
    new IUserInputAdaptor(m_userInput);

    webpagewindow *wpw = new webpagewindow();
    new IWebPageWindowAdaptor(wpw);

    BrowserView *bvi = new BrowserView(m_cacheManager, m_userInput);

    bvi->setGeometry(a_oGeometry.i32X, a_oGeometry.i32Y, a_oGeometry.i32Width,
                         a_oGeometry.i32Height);
    bvi->show();
    a_hPageWindowHandle = bvi->winId();

    windowhash.insert(a_hPageWindowHandle, bvi->window());

    wpw->webitem = bvi;
    connect(bvi, SIGNAL(pageLoadFinished(bool)),       wpw,  SLOT(getUrlTitle()));
    connect(bvi, SIGNAL(pageLoadStarted()),            wpw,  SLOT(browserStartLoading()));
    connect(bvi, SIGNAL(onVisibilityChanged(bool)),    wpw,  SIGNAL(onVisibilityChanged(bool)));
    connect(bvi, SIGNAL(pageLoadFinished(bool)),       wpw,  SIGNAL(onLoadFinished(bool)));
    connect(bvi, SIGNAL(onUrlChanged(QString)),        wpw,  SIGNAL(onUrlChanged(QString)));
    connect(bvi, SIGNAL(onTitleChanged(QString)),      wpw,  SIGNAL(onTitleChanged(QString)));
    connect(bvi, SIGNAL(onLinkClicked(QString)),       wpw,  SIGNAL(onLinkClicked(QString)));
    connect(bvi, SIGNAL(onSelectionChanged(void)),     wpw,  SIGNAL(onSelectionChanged(void)));
    connect(bvi, SIGNAL(onStatusTextChanged(QString)), wpw,  SIGNAL(onStatusTextChanged(QString)));
    connect(bvi, SIGNAL(onZoomFactorChanged(double)),  wpw,  SIGNAL(onZoomFactorChanged(double)));
    connect(bvi, SIGNAL(onLinkHovered(QString)),       wpw,  SIGNAL(onLinkHovered(QString)));
    connect(bvi, SIGNAL(onInputText(QString, QString, int, int, int, int, int)), m_userInput, SLOT(inputTextReceived(QString, QString, int, int, int, int, int)));
    connect(this,SIGNAL(onPageWindowDestroyed(qlonglong)), wpw, SIGNAL(onClose()));
    connect(bvi, SIGNAL(onScrollPositionChanged(uint,uint)), wpw, SIGNAL(onScrollPositionChanged(uint,uint)));
    connect(bvi, SIGNAL(onActionStateChanged(uint)),   wpw,  SIGNAL(onActionStateChanged(uint)));
    connect(bvi, SIGNAL(onContentSizeChanged(uint, uint)),wpw,SIGNAL(onContentSizeChanged(uint,uint)));
    connect(bvi, SIGNAL(onFaviconReceived()),           wpw,  SIGNAL(onFaviconReceived()));

    connect(m_userInput, SIGNAL(inputText(QString)),   bvi, SLOT(inputText(QString)));
    connect(bvi,         SIGNAL(onSelect(const QString &, const conn::brw::SelectableOptionList &, bool)),
            m_userInput, SIGNAL(onSelect(const QString &, const conn::brw::SelectableOptionList &, bool)));
    connect(m_userInput, SIGNAL(selectIndexes(QList<int>)), bvi, SLOT(onSelectIndexes(QList<int>)));

    QDBusConnection conn = connection();

    QString *webpagewindowservice = new QString("/Browser/IWebPageWindow" + QString::number(a_hPageWindowHandle));
    qDebug() << *webpagewindowservice;

    webviewhash.insert(*webpagewindowservice, bvi);

    if(!conn.registerObject(*webpagewindowservice, wpw)) {
        qDebug() << "failed register object IWebPageWindow";
        exit(1);
    }

    QString *userinputservice = new QString( *webpagewindowservice + "/IUserInput");
    qDebug() << *userinputservice;
    if(!conn.registerObject(*userinputservice, m_userInput)) {
        qDebug() << "failed register object IUserInput";
        exit(1);
    }

    emit onPageWindowCreated(a_hPageWindowHandle, conn::brw::EID_NO_ERROR);
    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS browser::destroyPageWindow(conn::brw::OBJECT_HANDLE a_hPageWindowHandle) {
    qDebug() << __PRETTY_FUNCTION__ << a_hPageWindowHandle;

    if(!windowhash.isEmpty()) {
        QWidget *tempwidget = windowhash.value(a_hPageWindowHandle);
        if(tempwidget) {
            windowhash.remove(a_hPageWindowHandle);
            tempwidget->hide();
            emit onPageWindowDestroyed(a_hPageWindowHandle);
            return conn::brw::EID_NO_ERROR;
        }
        return conn::brw::EID_DB_ITEM_NOT_EXISTS;
    }
    return conn::brw::EID_NOT_EXISTS;
}

conn::brw::ERROR_IDS browser::getPageWindows(conn::brw::ObjectHandleList &a_oPageWindowIds) {
    qDebug() << __PRETTY_FUNCTION__;

    conn::brw::ERROR_IDS ret;

    if(windowhash.isEmpty()) {
        ret = conn::brw::EID_NOT_EXISTS;
    } else {
        a_oPageWindowIds = windowhash.keys();
        ret =  conn::brw::EID_NO_ERROR;
    }
    return ret;
}
