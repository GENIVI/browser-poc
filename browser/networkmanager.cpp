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
#include <QNetworkReply>

networkmanager::networkmanager(QNetworkAccessManager *nam, QObject *parent) :
    QObject(parent), m_nam (nam)
{
    qDebug() << __PRETTY_FUNCTION__;

    connect(nam, SIGNAL(authenticationRequired(QNetworkReply *, QAuthenticator *)),
            this,SLOT  (onAuthenticationRequired(QNetworkReply *, QAuthenticator *)));
    connect(nam, SIGNAL(sslErrors(QNetworkReply *, const QList<QSslError> &)),
            this,SLOT  (onSslErrors(QNetworkReply *, const QList<QSslError> &)));
}

conn::brw::ERROR_IDS networkmanager::closeAuthenticationDialog(conn::brw::DIALOG_RESULT res, const conn::brw::AuthenticationData& data)
{
    emit doCloseAuthenticationDialog(res == conn::brw::DR_OK, data);
    return conn::brw::EID_NO_ERROR;
}
conn::brw::ERROR_IDS networkmanager::closeSslErrorDialog(conn::brw::DIALOG_RESULT res, bool saveCert)
{
    emit doCloseSslErrorDialog(res == conn::brw::DR_OK, saveCert);
    return conn::brw::EID_NO_ERROR;
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

void networkmanager::onSslErrors(QNetworkReply *reply, const QList<QSslError> & errors)
{
    conn::brw::SslError data;
    data.sslError = conn::brw::UnableToGetIssuerCertificate; 
    emit onSslErrorDialog(data);
    qDebug() << "SSL error; action required";
    QEventLoop loop;
    connect (this, SIGNAL(doCloseSslErrorDialog(bool, bool)), this, SLOT(closeSsl(bool, bool)));
    connect (this, SIGNAL(doCloseSslErrorDialog(bool, bool)), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << "SSL error action provided: isOK" << m_isSslOk << "save cert:" << m_sslSaveCert;

    if (m_isSslOk) {
        reply->ignoreSslErrors();
        qDebug() << "Ignoring error";
    } else {
        qDebug() << "Halting on error";
    }
}
