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

#include "../common/browserdefs.h"

class userinput : public QObject
{
    Q_OBJECT
public:
    explicit userinput(QObject *parent = 0);
    
signals:
    void onInputText(QString a_strInputName, QString a_strDefaultInputValue, QString a_i32InputValueType, int a_s32MaxLength, int a_s32Max, int a_s32Min, int a_s32Step);
    void inputText(QString input);
    
public Q_SLOTS:
    conn::brw::ERROR_IDS inputText(conn::brw::DIALOG_RESULT a_eResult, const QString &a_strInputValue);
};

#endif // USERINPUT_H
