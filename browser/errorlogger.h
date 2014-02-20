/**
 * Copyright (C) 2014, Pelagicore
 *
 * Author: Jonatan Pålsson <jonatan.palsson@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include <QObject>
#include <QDBusContext>

#include "../common/browserdefs.h"

class errorlogger : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    errorlogger(QObject *parent = 0);

signals:
    void onErrorListChanged();
    void onNewErrorItem (const conn::brw::ErrorItem);

public Q_SLOTS:
    uint getItemsCount (qlonglong, qlonglong);
    conn::brw::ERROR_IDS getItems (qlonglong timeFrom,
                                   qlonglong timeTo,
                                   conn::brw::ERROR_SORT_TYPE sortType,
                                   uint startIndex,
                                   uint itemsCount,
                                   conn::brw::ErrorItemList items);

private:
};

#endif // ERRORLOGGER_H
