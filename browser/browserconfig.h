/**
 * Copyright (C) 2014, Pelagicore
 *
 * Author: Jonatan Palsson <jonatan.palsson@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <QObject>
#include <QSettings>

#include "../common/browserdefs.h"

class BrowserConfig : public QObject{
Q_OBJECT
public:
   enum BrowserConfigKey {CONFIG_CACHEPOLICY};
   BrowserConfig();

   template<typename T>
   T getValue(BrowserConfigKey);

   template<typename T>
   void setValue(BrowserConfigKey, T);

   bool contains(BrowserConfig::BrowserConfigKey key);

private:
    QSettings *m_qsettings = NULL;
};
