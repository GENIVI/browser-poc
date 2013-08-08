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
#include <QGraphicsObject>
#include <QDeclarativeView>
#include <QTimer>

#include "webpagewindow.h"

class browserhelper : public QObject
{
    Q_OBJECT
public:
    explicit browserhelper(QObject *parent = 0);

    QGraphicsObject *webitem;
    webpagewindow *wpw;
    QDeclarativeView *view;

signals:
    void onLoadStarted();
    void onLoadProgress(int progress);

public slots:
    void browserreload();
    void browserback();
    void browserforward();
    void browserstop();
    void browserloadurl(QString url);

    void getUrlTitle();

    void reportprogress();

    void browserStartLoading();

    void createWindow(int x, int y, int width, int height);
    void destroyWindow();

private:
    QTimer *progresstimer;
    
};

#endif // BROWSERHELPER_H
