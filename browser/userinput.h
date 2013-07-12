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

#include "../browserdefs.h"

class userinput : public QObject
{
    Q_OBJECT
public:
    explicit userinput(QObject *parent = 0);
    
signals:
    
public Q_SLOTS:
    conn::brw::ERROR_IDS inputText(conn::brw::DIALOG_RESULT a_eResult, const QString &a_strInputValue);
    
};

#endif // USERINPUT_H
