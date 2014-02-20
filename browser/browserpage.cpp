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

#include <QWebFrame>
#include <QDebug>
#include <QEventLoop>

#include "browserpage.h"
#include "userinput.h"

void BrowserPage::javaScriptAlert(QWebFrame *frame, const QString &message)
{
    Q_UNUSED(frame);
    emit onAlertDialog(message);
    QEventLoop loop;
    qDebug() << "Alert dialog opened:" << message;
    connect (m_userInput, SIGNAL(doCloseAlertDialog(void)), &loop, SLOT(quit(void)));
    loop.exec();
    qDebug() << "Alert dialog closed";
}

bool BrowserPage::javaScriptConfirm(QWebFrame *frame, const QString &message)
{
    Q_UNUSED(frame);
    emit onConfirmDialog(message);
    QEventLoop loop;
    qDebug() << "Confirm dialog opened:" << message;
    connect (m_userInput, SIGNAL(doCloseConfirmDialog(bool)), this, SLOT(confirm(bool)));
    connect (m_userInput, SIGNAL(doCloseConfirmDialog(bool)), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << "Confirm dialog closed:" << m_confirm;
    return m_confirm;
}
bool BrowserPage::javaScriptPrompt(QWebFrame *frame, const QString &msg, const QString &defaultValue, QString *result )
{
    Q_UNUSED(frame);
    emit onPromptDialog(msg, defaultValue);
    QEventLoop loop;
    qDebug() << "Confirm dialog opened (default:" << defaultValue << ")";
    connect (m_userInput, SIGNAL(doClosePromptDialog(QString, bool)), this, SLOT(prompt(QString, bool)));
    connect (m_userInput, SIGNAL(doClosePromptDialog(QString, bool)), &loop, SLOT(quit()));
    loop.exec();
    *result = m_promptStr;
    qDebug() << "Confirm dialog closed:" << m_promptBool << m_promptStr;
    return m_promptBool;
}
