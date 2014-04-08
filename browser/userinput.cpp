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
    QObject(parent), m_inputHistory(new QList<struct inputStruct>())
{
    qDebug() << __PRETTY_FUNCTION__;
}

conn::brw::ERROR_IDS userinput::inputText(conn::brw::DIALOG_RESULT a_eResult, const QString &a_strInputValue) {
    qDebug() << __PRETTY_FUNCTION__ << a_eResult << a_strInputValue;

    if(a_eResult == conn::brw::DR_OK) {
            emit inputText(a_strInputValue);

        struct inputStruct is;
        is.name = m_currentInput.name;
        is.type = m_currentInput.type;
        is.value = a_strInputValue;
        bool shouldAdd = true;

        for (int i = 0; i < m_inputHistory->size(); i++) {
            if (m_inputHistory->at(i).value.compare(is.value) == 0 &&
                m_inputHistory->at(i).type == is.type              &&
                m_inputHistory->at(i).name == is.name) {
                shouldAdd = false;
                break;
            }
        }

        qDebug() << "Should add " << is.value << "?" << shouldAdd;

        if (shouldAdd)
            m_inputHistory->append(is);
    }

    return conn::brw::EID_NO_ERROR;
}

void userinput::inputTextReceived(QString a_strInputName, QString a_strDefaultInputValue, int a_i32InputValueType, int a_s32MaxLength, int a_s32Max, int a_s32Min, int a_s32Step) {
    qDebug() << __PRETTY_FUNCTION__;

    m_currentInput.name = a_strInputName;
    m_currentInput.type = (conn::brw::INPUT_ELEMENT_TYPE)a_i32InputValueType;

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

conn::brw::ERROR_IDS userinput::getPrevEnteredValues (const QString &a_strInputName, const QString &a_strInputValue, conn::brw::INPUT_ELEMENT_TYPE a_i32InputType, QStringList &a_oInputVariants)
{
    Q_UNUSED(a_strInputValue);
    for (int i = 0; i < m_inputHistory->size(); i++){
        struct inputStruct s = m_inputHistory->at(i);
        qDebug() << s.value;
        if (s.type == a_i32InputType            &&
            s.name.compare(a_strInputName) == 0 &&
            s.value.contains(a_strInputValue,
                             Qt::CaseInsensitive))
        {
            a_oInputVariants.append(s.value);
        }
    }

    return conn::brw::EID_NO_ERROR;
}

conn::brw::ERROR_IDS userinput::selectOption(const conn::brw::SelectableOptionList &a_oOptionList)
{
    QList<int> indexes;
    for (int i = 0; i < a_oOptionList.size(); i++) {
        if (a_oOptionList.at(i).bSelected) {
            indexes.append(i);
        }
    }

    emit selectIndexes (indexes);
    return conn::brw::EID_NO_ERROR;
}
