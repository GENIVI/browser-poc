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

class webpagewindow;
class QDBusConnection;

class browserhelper : public QObject
{
    Q_OBJECT
public:
    explicit browserhelper(QString instanceId, QObject *parent = 0);

private:
    QDBusConnection *connection;
    webpagewindow *wpw;
    void registertypes();
};

#endif // BROWSERHELPER_H
