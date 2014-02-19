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

#include "networkmanager.h"
#include <QDebug>
#include <QDBusMessage>
#include <QAuthenticator>
#include <QEventLoop>

networkmanager::networkmanager(QNetworkAccessManager *nam, QObject *parent) :
    QObject(parent), m_nam (nam)
{
    qDebug() << __PRETTY_FUNCTION__;

    connect(nam, SIGNAL(authenticationRequired(QNetworkReply *, QAuthenticator *)),
            this,SLOT  (onAuthenticationRequired(QNetworkReply *, QAuthenticator *)));
}

conn::brw::ERROR_IDS networkmanager::closeAuthenticationDialog(conn::brw::DIALOG_RESULT res, const conn::brw::AuthenticationData& data)
{
    emit doCloseAuthenticationDialog(res == conn::brw::DR_OK, data);
    return conn::brw::EID_NO_ERROR;
}
conn::brw::ERROR_IDS networkmanager::closeSslErrorDialog(conn::brw::DIALOG_RESULT res, bool saveCert)
{
}

void networkmanager::onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    conn::brw::AuthenticationData data;
    emit onAuthenticationDialog(data);
    qDebug() << "Authentication required";
    QEventLoop loop;
    connect (this, SIGNAL(doCloseAuthenticationDialog(bool, const conn::brw::AuthenticationData)), this, SLOT(authenticate(bool, const conn::brw::AuthenticationData)));
    connect (this, SIGNAL(doCloseAuthenticationDialog(bool, const conn::brw::AuthenticationData)), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << "Authentication provided: user" << m_authData.strUserName << "password:" << m_authData.strPassword;

    if (m_authBool) {
        authenticator->setUser(m_authData.strUserName);
        authenticator->setPassword(m_authData.strPassword);
    } else {
        qDebug() << "Action was cancelled";
    }
}
