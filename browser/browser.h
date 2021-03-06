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
#include <QDBusContext>

#include "../common/browserdefs.h"
#include "webpagewindow.h"
#include "userinput.h"
#include "browserview.h"
#include "cachemanager.h"
#include "userinput.h"
#include "networkmanager.h"

class browser : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    explicit browser(cachemanager *, networkmanager *, QObject *parent = 0);

    webpagewindow *wpw;

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
    QHash<QString, BrowserView *> webviewhash;
    cachemanager *m_cacheManager;
    userinput    *m_userInput;
    networkmanager *m_networkManager;
};

#endif // BROWSER_H
