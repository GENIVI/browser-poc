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

#include "../browserdefs.h"

class webpagewindow : public QObject
{
    Q_OBJECT
public:
    explicit webpagewindow(QObject *parent = 0);
    
signals:
    
public Q_SLOTS:
    conn::brw::ERROR_IDS back();
    conn::brw::ERROR_IDS forward();
    conn::brw::ERROR_IDS getBrowserActionsState();
    conn::brw::ERROR_IDS getContentSize();
    conn::brw::ERROR_IDS getGeometry();
    bool getVisible();
    conn::brw::ERROR_IDS load(const QString &a_Url);
    conn::brw::ERROR_IDS reload();
    conn::brw::ERROR_IDS scroll(conn::brw::SCROLL_DIRECTION a_eScrollDirection, conn::brw::SCROLL_TYPE a_eScrollType);
    conn::brw::ERROR_IDS setGeometry(const conn::brw::Rect & a_sRect);
    conn::brw::ERROR_IDS setVisible(bool a_bVisible);
    conn::brw::ERROR_IDS stop();
};

#endif // WEBPAGEWINDOW_H
