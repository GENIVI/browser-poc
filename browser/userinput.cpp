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

#include "userinput.h"
#include <QDebug>
#include <QDBusMessage>

userinput::userinput(QObject *parent) :
    QObject(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
}

conn::brw::ERROR_IDS userinput::inputText(conn::brw::DIALOG_RESULT a_eResult, const QString &a_strInputValue) {
    qDebug() << __PRETTY_FUNCTION__ << a_eResult << a_strInputValue;

    emit setOutputWebview(message().path());

    if(a_eResult == conn::brw::DR_OK)
        emit inputText(a_strInputValue);

    return conn::brw::EID_NO_ERROR;
}

void userinput::inputTextReceived(QString a_strInputName, QString a_strDefaultInputValue, int a_i32InputValueType, int a_s32MaxLength, int a_s32Max, int a_s32Min, int a_s32Step) {
    qDebug() << __PRETTY_FUNCTION__;

    emit onInputText(a_strInputName, a_strDefaultInputValue, (conn::brw::INPUT_ELEMENT_TYPE)a_i32InputValueType, a_s32MaxLength, a_s32Max, a_s32Min, a_s32Step);
}

conn::brw::ERROR_IDS userinput::closeAlertDialog (void)
{
    emit doCloseAlertDialog();
    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS userinput::closeConfirmDialog (conn::brw::DIALOG_RESULT b)
{
    switch (b) {
        case conn::brw::DR_OK:
            emit doCloseConfirmDialog(true);
            break;
        case conn::brw::DR_CANCEL:
            emit doCloseConfirmDialog(false);
            emit onDialogCanceled();
            break;
        default:
            qDebug() << "Bad value for conn::brw::DIALOG_RESULT";
    }
    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS userinput::closePromptDialog(QString resultStr, conn::brw::DIALOG_RESULT resultEn)
{
    switch (resultEn) {
        case conn::brw::DR_OK:
            emit doClosePromptDialog(resultStr, true);
            break;
        case conn::brw::DR_CANCEL:
            emit doClosePromptDialog(resultStr, false);
            emit onDialogCanceled();
            break;
        default:
            qDebug() << "Bad value for conn::brw::DIALOG_RESULT";
    }
    return conn::brw::EID_NO_ERROR;
}
