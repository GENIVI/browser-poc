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

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "ibookmarkmanager_interface.h"
#include "iuserinput_interface.h"
#include "iwebpagewindow_interface.h"
#include "ibrowser_interface.h"


class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void getItems();
    void deleteAllItems();
    void input();
    void reload();
    void B1addpressed();
    void B2addpressed();
    void B3addpressed();
    void B4addpressed();
    void B5addpressed();
    void B1deletepressed();
    void B2deletepressed();
    void B3deletepressed();
    void B4deletepressed();
    void B5deletepressed();

private:
    conn::brw::IBookmarkManager *bookmark;
    conn::brw::IUserInput *userinput;
    conn::brw::IWebPageWindow *webpagewindow;
    conn::brw::IBrowser *browser;

    void addItem(int bookmarknumber);
    void deleteItem(int bookmarknumber);

    QList<conn::brw::BookmarkItem> bookmarklist;
    void initializebookmarks();
};

#endif // WIDGET_H
