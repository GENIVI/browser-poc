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
#ifndef BROWSERCONFIG_H
#define BROWSERCONFIG_H

#include <QObject>
#include <QSettings>

#include "../common/browserdefs.h"

class BrowserConfig : public QObject{
Q_OBJECT
public:
    enum BrowserConfigKey {
        CONFIG_CACHEPOLICY,
        CONFIG_STARTPAGE,
    };

    static BrowserConfig* instance()  {
        if (!BrowserConfig::m_config)
            BrowserConfig::m_config = new BrowserConfig();

        return BrowserConfig::m_config;
    }

    template<typename T>
    T getValue(BrowserConfigKey);

    template<typename T>
    void setValue(BrowserConfigKey, T);

    bool contains(BrowserConfig::BrowserConfigKey key);

private:
    BrowserConfig();
    QSettings *m_qsettings;
    static BrowserConfig *m_config;
};

#endif /*BROWSERCONFIG_H*/
