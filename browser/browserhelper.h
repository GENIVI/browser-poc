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

#ifndef BROWSERHELPER_H
#define BROWSERHELPER_H

#include <QObject>

#include <QQuickItem>

#include "webpagewindow.h"

class browserhelper : public QObject
{
    Q_OBJECT
public:
    explicit browserhelper(QObject *parent = 0);

    QQuickItem *webitem;
    webpagewindow *wpw;

signals:
    
public slots:
    void browserreload();
    void browserback();
    void browserforward();
    void browserstop();
    void browserloadurl(QString url);

    void getUrlTitle();

private:

    
};

#endif // BROWSERHELPER_H