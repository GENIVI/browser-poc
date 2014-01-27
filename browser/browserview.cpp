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

#include <QDebug>
#include <QWebFrame>
#include <QCoreApplication>

#include "browserview.h"
#include "../common/browserdefs.h"

BrowserView::BrowserView()
{
    if (!this->scene()) {
        this->setScene(new QGraphicsScene());
    }
    this->scene()->addItem (&m_webview);

    this->load("http://www.bmw.com");

    setWindowFlags(Qt::FramelessWindowHint);

    connect(&m_webview, SIGNAL (loadStarted()),      this, SIGNAL (pageLoadStarted ()));
    connect(&m_webview, SIGNAL (loadFinished(bool)), this, SIGNAL (pageLoadFinished (bool)));
    connect(&m_webview, SIGNAL (loadProgress(int)),  this, SLOT   (loadProgress(int)));
}

bool BrowserView::load(const QString &a_Url)
{
    m_webview.load(a_Url);
    return true;
}

void BrowserView::loadProgress(int progress)
{
    m_currentProgress = progress;
    emit pageLoadProgress (progress);
}
void BrowserView::scroll (conn::brw::SCROLL_DIRECTION dir, conn::brw::SCROLL_TYPE type)
{
    int stepSize = 50;
    int xMultiplier = 0;
    int yMultiplier = 0;

    switch (dir) {
    case conn::brw::SD_TOP:
        yMultiplier = -1;
        break;
    case conn::brw::SD_BOTTOM:
        yMultiplier = 1;
        break;
    case conn::brw::SD_RIGHT:
        xMultiplier = 1;
        break;
    case conn::brw::SD_LEFT:
        xMultiplier = -1;
        break;
    default:
        qDebug() << "Invalid direction";
        break;
    }

    if (type == conn::brw::ST_PAGE)
        stepSize= this->height();

    if (m_webview.page() && m_webview.page()->mainFrame())
        m_webview.page()->mainFrame()->scroll(stepSize*xMultiplier,
                                              stepSize*yMultiplier);
}

void BrowserView::inputText (QString input)
{
	QInputMethodEvent event;
	event.setCommitString(input);
	QCoreApplication::sendEvent(m_webview.page(), &event);
}

void BrowserView::resizeEvent (QResizeEvent *event) {
    int w = event->size().width();
    int h = event->size().height();
    m_webview.setGeometry (QRect(0,0,w,h));
}

QSize BrowserView::contentSize()
{
    return this->viewport()->size();
}
