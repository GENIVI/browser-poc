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
#include <QDateTime>

#include "../common/browserdefs.h"

class errorlogger : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    static errorlogger *instance()
    {
        if (!m_instance)
            m_instance = new errorlogger();
        return m_instance;
    }

    static void logError (qlonglong dateTime,
                          QString browserVersion,
                          QString connectionType,
                          QString code,
                          QString source,
                          QString desc)
    {
        conn::brw::ErrorItem err;
        err.i64DateTime = dateTime;
        err.strBrowserVersion = browserVersion;
        err.strConnectionType = connectionType;
        err.strCode = code;
        err.strSource = source;
        err.strDescription = desc;
        errorlogger::logError(err);
    }

    static void logError(QString error)
    {
        errorlogger::logError(
                QDateTime::currentDateTime().toTime_t(),
                "Unknown",
                "Unknown",
                "Unknown",
                "Unknown",
                error);
    }

    static void logError(conn::brw::ErrorItem item)
    {
        m_instance->m_logError(item);
    }

    void clearErrors()
    {
        m_errors->clear();
        emit onErrorListChanged();
    }
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
                                   conn::brw::ErrorItemList &items);

private:
    errorlogger(){
        m_errors = new conn::brw::ErrorItemList();
    }
    static errorlogger *m_instance;

    void m_logError(conn::brw::ErrorItem);

    conn::brw::ErrorItemList *m_errors;
};

#endif // ERRORLOGGER_H
