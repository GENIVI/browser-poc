/**
 * Copyright (C) 2013, Pelagicore
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

#include <QObject>
#include <QDBusContext>
#include <QDebug>
#include <QAbstractNetworkCache>
#include <QNetworkDiskCache>

#include "errorlogger.h"
#include "../common/browserdefs.h"

errorlogger::errorlogger(QObject *parent) :
    QObject(parent)
{}

uint errorlogger::getItemsCount(qlonglong timeFrom, qlonglong timeTo)
{
    return 0;
}
conn::brw::ERROR_IDS errorlogger::getItems(qlonglong timeFrom,
                                           qlonglong timeTo,
                                           conn::brw::ERROR_SORT_TYPE type,
                                           uint startIndex,
                                           uint itemsCount,
                                           conn::brw::ErrorItemList items)
{
    return conn::brw::EID_NO_ERROR;
}
