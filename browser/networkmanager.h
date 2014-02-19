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

#ifndef NETWORKMAMAGER_H
#define NETWORKMAMAGER_H

#include <QObject>
#include <QDBusContext>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QAuthenticator>

#include "../common/browserdefs.h"

class networkmanager : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    explicit networkmanager(QNetworkAccessManager *nam, QObject *parent = 0);


signals:
    void onAuthenticationDialog(const conn::brw::AuthenticationData &);
    void onAuthenticationDialogCancel(conn::brw::AuthenticationData &);
    void onSslErrorDialog(const conn::brw::SslError &);
    void onSslErrorDialogCancel(const conn::brw::SslError &);

    // Internal
    void doCloseAuthenticationDialog(bool, const conn::brw::AuthenticationData);
    void doCloseSslErrorDialog(bool, bool);

public Q_SLOTS:
    conn::brw::ERROR_IDS closeAuthenticationDialog(conn::brw::DIALOG_RESULT, const conn::brw::AuthenticationData&);
    conn::brw::ERROR_IDS closeSslErrorDialog(conn::brw::DIALOG_RESULT, bool);

    // Internal
    void onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void onSslErrors(QNetworkReply *reply, const QList<QSslError> & errors);
    void authenticate(bool b, const conn::brw::AuthenticationData ad)
    {
        m_authBool = b;
        m_authData = ad;
    }
    void closeSsl(bool isOK, bool saveCert)
    {
        m_isSslOk = isOK;
        m_sslSaveCert = saveCert;
    }
private:
    QNetworkAccessManager *m_nam;
    bool m_authBool, m_isSslOk, m_sslSaveCert;
    conn::brw::AuthenticationData m_authData;
};

#endif // NETWORKMAMAGER_H
