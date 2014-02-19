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

#include <QtTest/QtTest>
#include "../../../common/browserdbus.h"
#include "webpagegenerator.h"

class TestBrowserDBus: public QObject
{
	Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testCallUninitialized();
    void testGetTitle();
    void testGetsNotifiedOnUrlChange();
    void testGetsNotifiedOnTitleChange();
    void testGetsNotifiedWhenLinkIsClicked();
    void testGetsNotifiedWhenLinkIsHovered();
    void testGetsNotifiedWhenSelectionChanges();
    void testGetsNotifiedWhenStatusBarChanges();
    void testGetsNotifiedWhenVisibilityChanges();
    void testGetsNotifiedWhenScrollingChanges();
    void testCanSetAndGetZoomFactor();
    void testCanSetAndGetScrollPosition();
    void testCanGeneratePageIcon();
    void testCanGetFavicon();
    void testOnActionStateChanged();
    void testOnContentSizeChanged();
    void testOnFaviconReceived();
    void testSelect();
    void testActivate();
    void testConfirmDialog();
    void testCancelConfirmDialog();
    void testPromptDialog();
    void testCancelPromptDialog();
    void testAlertDialog();
    void testGetPrevEnteredValues();
    void testGetsNotifiedWhenSelectIsSelected();
    void testGetsNotifiedOnAuthDialog();
    void testCanCloseAuthDialog();

private:
    QString testFileUrl() {
        return (QString ("file://") + m_pagefile->fileName());
    }
    BrowserDbus    *m_bdb;
    QTemporaryFile *m_pagefile;
};
