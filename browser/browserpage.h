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

#ifndef BROWSERPAGE_H
#define BROWSERPAGE_H

#include <QWebPage>
#include <QObject>

#include "userinput.h"

class BrowserPage : public QWebPage {
Q_OBJECT

public:
    BrowserPage(QObject *parent, userinput *input) 
        : QWebPage (parent), m_userInput (input){
        connect(this,        SIGNAL(onAlertDialog(QString)),
                m_userInput, SIGNAL(onAlertDialog(QString)));
        connect(this,        SIGNAL(onConfirmDialog(QString)),
                m_userInput, SIGNAL(onConfirmDialog(QString)));
        connect(this,        SIGNAL(onPromptDialog(QString, QString)),
                m_userInput, SIGNAL(onPromptDialog(QString, QString)));
        }
    ~BrowserPage(){ }

signals:
    void onAlertDialog(QString);
    void onConfirmDialog(QString);
    void onPromptDialog(QString, QString);

protected:
    void javaScriptAlert(QWebFrame *frame, const QString &message);
    bool javaScriptConfirm(QWebFrame *frame, const QString &message);
    bool javaScriptPrompt (QWebFrame *, const QString &, const QString &, QString *);

protected slots:
    void confirm(bool b) {m_confirm = b;}
    void prompt (QString s, bool b) {m_promptBool = b; m_promptStr = s;}

private:
    userinput *m_userInput;
    bool m_confirm;
    bool m_promptBool;
    QString m_promptStr;
};

#endif /* BROWSERPAGE_H */
