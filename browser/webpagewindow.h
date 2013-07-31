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

#ifndef WEBPAGEWINDOW_H
#define WEBPAGEWINDOW_H

#include <QObject>

#include "../common/browserdefs.h"

#include <QQuickItem>

class webpagewindow : public QObject
{
    Q_OBJECT
public:
    explicit webpagewindow(QObject *parent = 0);


    QString localurl;
    QString localtitle;

signals:
    void reloadrequested();
    void backrequested();
    void forwardrequested();
    void stoprequested();
    void loadurlrequested(QString url);
    void test();
    
public Q_SLOTS:
    conn::brw::ERROR_IDS back();
    conn::brw::ERROR_IDS forward();
    conn::brw::ERROR_IDS getBrowserActionsState(conn::brw::BrowserActions &a_browserActionsState);
    conn::brw::ERROR_IDS getContentSize(uint &a_u32Width, uint &a_u32Height);
    conn::brw::ERROR_IDS getGeometry(conn::brw::Rect &a_sRect);
    bool getVisible();
    conn::brw::ERROR_IDS load(const QString &a_Url);
    conn::brw::ERROR_IDS reload();
    conn::brw::ERROR_IDS scroll(conn::brw::SCROLL_DIRECTION a_eScrollDirection, conn::brw::SCROLL_TYPE a_eScrollType);
    conn::brw::ERROR_IDS setGeometry(const conn::brw::Rect & a_sRect);
    conn::brw::ERROR_IDS setVisible(bool a_bVisible);
    conn::brw::ERROR_IDS stop();
    conn::brw::ERROR_IDS getCurrentUrlTitle(QString &url, QString &title);
//    conn::brw::ERROR_IDS getCurrentUrlTitle(QString url);
//    QString getCurrentUrlTitle(QString &test);
};

#endif // WEBPAGEWINDOW_H
