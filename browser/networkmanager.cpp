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
#include <QSslError>
#include <QSslSocket>

conn::brw::SslError convertError(QSslError err, const QNetworkReply *rep)
{
    conn::brw::SslError data;
    data.strUrl = rep->url().toString();
    data.strErrorMessage = err.errorString();

    switch (err.error()) {
    case(QSslError::NoError):
        {data.sslError = conn::brw::NoError; break;}
    case(QSslError::UnableToGetIssuerCertificate):
        {data.sslError = conn::brw::UnableToGetIssuerCertificate; break;}
    case(QSslError::UnableToDecryptCertificateSignature):
        {data.sslError = conn::brw::UnableToDecryptCertificateSignature; break;}
    case(QSslError::UnableToDecodeIssuerPublicKey):
        {data.sslError = conn::brw::UnableToDecodeIssuerPublicKey; break;}
    case(QSslError::CertificateSignatureFailed):
        {data.sslError = conn::brw::CertificateSignatureFailed; break;}
    case(QSslError::CertificateNotYetValid):
        {data.sslError = conn::brw::CertificateNotYetValid; break;}
    case(QSslError::CertificateExpired):
        {data.sslError = conn::brw::CertificateExpired; break;}
    case(QSslError::InvalidNotBeforeField):
        {data.sslError = conn::brw::InvalidNotBeforeField; break;}
    case(QSslError::InvalidNotAfterField):
        {data.sslError = conn::brw::InvalidNotAfterField; break;}
    case(QSslError::SelfSignedCertificate):
        {data.sslError = conn::brw::SelfSignedCertificate; break;}
    case(QSslError::SelfSignedCertificateInChain):
        {data.sslError = conn::brw::SelfSignedCertificateInChain; break;}
    case(QSslError::UnableToGetLocalIssuerCertificate):
        {data.sslError = conn::brw::UnableToGetLocalIssuerCertificate; break;}
    case(QSslError::UnableToVerifyFirstCertificate):
        {data.sslError = conn::brw::UnableToVerifyFirstCertificate; break;}
    case(QSslError::CertificateRevoked):
        {data.sslError = conn::brw::CertificateRevoked; break;}
    case(QSslError::InvalidCaCertificate):
        {data.sslError = conn::brw::InvalidCaCertificate; break;}
    case(QSslError::PathLengthExceeded):
        {data.sslError = conn::brw::PathLengthExceeded; break;}
    case(QSslError::InvalidPurpose):
        {data.sslError = conn::brw::InvalidPurpose; break;}
    case(QSslError::CertificateUntrusted):
        {data.sslError = conn::brw::CertificateUntrusted; break;}
    case(QSslError::CertificateRejected):
        {data.sslError = conn::brw::CertificateRejected; break;}
    case(QSslError::SubjectIssuerMismatch):
        {data.sslError = conn::brw::SubjectIssuerMismatch; break;}
    case(QSslError::AuthorityIssuerSerialNumberMismatch):
        {data.sslError = conn::brw::AuthorityIssuerSerialNumberMismatch; break;}
    case(QSslError::NoPeerCertificate):
        {data.sslError = conn::brw::NoPeerCertificate; break;}
    case(QSslError::HostNameMismatch):
        {data.sslError = conn::brw::HostNameMismatch; break;}
    case(QSslError::UnspecifiedError):
        {data.sslError = conn::brw::UnspecifiedError; break;}
    case(QSslError::NoSslSupport):
        {data.sslError = conn::brw::NoSslSupport; break;}
    case(QSslError::CertificateBlacklisted):
        {data.sslError = conn::brw::CertificateBlacklisted; break;}
    }

    return data;
}

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
    for (int i = 0; i < errors.size(); i++) {
        conn::brw::SslError data = convertError (errors.at(i), reply);
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

        if (m_sslSaveCert) {
            qDebug() << "Saving certificate";
            QSslSocket::addDefaultCaCertificate(errors.at(i).certificate());
        } else {
            qDebug() << "Not saving certificate";
        }
    }
}

