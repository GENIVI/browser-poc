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

#ifndef USERINPUT_H
#define USERINPUT_H

#include <QObject>
#include <QDBusContext>
#include <QDebug>

#include "../common/browserdefs.h"



class userinput : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    explicit userinput(QObject *parent = 0);
    
signals:
    void onInputText(QString a_strInputName, QString a_strDefaultInputValue,
                     conn::brw::INPUT_ELEMENT_TYPE a_i32InputValueType, int a_s32MaxLength,
                     int a_s32Max, int a_s32Min, int a_s32Step);
    void inputText(QString input);
    void setOutputWebview(QString path);
    void onConfirmDialog(QString);
    void onPromptDialog(QString,QString);
    void onAlertDialog(QString);
    void onDialogCanceled(void);
    void onSelect(const QString &a_strSelectName, const conn::brw::SelectableOptionList & a_oOptions, bool a_bMultiSelectionAllowed);

    // Internal
    void doCloseAlertDialog(void);
    void doCloseConfirmDialog(bool);
    void doClosePromptDialog(QString, bool);
    void selectIndexes(QList<int>);
    
public Q_SLOTS:
    conn::brw::ERROR_IDS inputText(conn::brw::DIALOG_RESULT a_eResult, const QString &a_strInputValue);
    void inputTextReceived(QString a_strInputName, QString a_strDefaultInputValue, int a_i32InputValueType,
                           int a_s32MaxLength, int a_s32Max, int a_s32Min, int a_s32Step);
    conn::brw::ERROR_IDS closeAlertDialog (void);
    conn::brw::ERROR_IDS closeConfirmDialog (conn::brw::DIALOG_RESULT);
    conn::brw::ERROR_IDS closePromptDialog (QString, conn::brw::DIALOG_RESULT);
    conn::brw::ERROR_IDS getPrevEnteredValues(const QString&, const QString&, conn::brw::INPUT_ELEMENT_TYPE, QStringList&);
    conn::brw::ERROR_IDS selectOption(const conn::brw::SelectableOptionList &);

private:
    struct inputStruct {
        QString name;
        QString value;
        conn::brw::INPUT_ELEMENT_TYPE type;
    };

    struct {
        QString name;
        conn::brw::INPUT_ELEMENT_TYPE type;
    } m_currentInput;

    QList<struct inputStruct> *m_inputHistory;
};

#endif // USERINPUT_H
