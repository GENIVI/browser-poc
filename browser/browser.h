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

#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>
#include <QDeclarativeView>

#include "../common/browserdefs.h"

#include <QtDBus/QDBusConnection>
#include "webpagewindow.h"
#include "userinput.h"

class browser : public QObject
{
    Q_OBJECT
public:
    explicit browser(QObject *parent = 0);
    
    QDeclarativeView *initialview;
    QDBusConnection *connection;
    webpagewindow *wpw;
    userinput *ui;

signals:
    void onPageWindowCreated(qlonglong a_hPageWindowHandle, conn::brw::ERROR_IDS a_eErrorId);
    void onPageWindowDestroyed(qlonglong a_hPageWindowHandle);

public Q_SLOTS:
    conn::brw::ERROR_IDS createPageWindow(int a_eDeviceId, const conn::brw::Rect & a_oGeometry,
                                          conn::brw::OBJECT_HANDLE &a_hPageWindowHandle);
    conn::brw::ERROR_IDS destroyPageWindow(qlonglong a_hPageWindowHandle);
    conn::brw::ERROR_IDS getPageWindows(conn::brw::ObjectHandleList &a_oPageWindowIds);
    
private:
    QHash<conn::brw::OBJECT_HANDLE, QWidget*> windowhash;
};

#endif // BROWSER_H
