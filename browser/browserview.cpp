#include "browserview.h"
#include <QDebug>

BrowserView::BrowserView()
{
    if (!this->scene()) {
        this->setScene(new QGraphicsScene());
    }
    this->scene()->addItem (&m_webview);

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
