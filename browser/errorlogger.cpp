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
#include <QDateTime>

#include "errorlogger.h"
#include "../common/browserdefs.h"

errorlogger* errorlogger::m_instance = NULL;

uint errorlogger::getItemsCount(qlonglong timeFrom, qlonglong timeTo)
{
    uint num = 0;
    for (int i = 0; i < m_errors->size(); i++) {
        const conn::brw::ErrorItem *e = &m_errors->at(i);
        if (timeFrom <= e->i64DateTime && timeTo >= e->i64DateTime)
            num++;
    }
    return num;
}
conn::brw::ERROR_IDS errorlogger::getItems(qlonglong timeFrom,
                                           qlonglong timeTo,
                                           conn::brw::ERROR_SORT_TYPE type,
                                           uint startIndex,
                                           uint itemsCount,
                                           conn::brw::ErrorItemList &items)
{
    if (type == conn::brw::EST_DATE_ASCENDING)
        qSort (m_errors->begin(), m_errors->end(), conn::brw::ltError);
    else
        qSort (m_errors->begin(), m_errors->end(), conn::brw::gtError);
    for (int i = 0; i < m_errors->size(); i++){
    }
    for (int i = startIndex; i < m_errors->size(); i++) {
        const conn::brw::ErrorItem e = m_errors->at(i);
        if (timeFrom <= e.i64DateTime && timeTo >= e.i64DateTime) {
            if (items.size() < itemsCount){
                items.append(e);
            }
            else
                break;
        }
    }
    return conn::brw::EID_NO_ERROR;
}


void errorlogger::m_logError(conn::brw::ErrorItem item) {
    m_errors->append(item);
    emit onNewErrorItem(item);
}
