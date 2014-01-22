#ifndef BROWSERVIEW_H
#define BROWSERVIEW_H

#include <QGraphicsWidget>
#include <QGraphicsWebView>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QRect>

class BrowserView : public QGraphicsView
{
     Q_OBJECT
public:
    BrowserView();
    bool load(const QString &a_Url);
    int getProgress() { return m_currentProgress; }
    QString getURL() { return m_webview.url().toString(); }
    const QString getTitle() { return m_webview.title(); }
    void goBack() { m_webview.back(); }
    void goForward() { m_webview.forward(); }
    void pageReload() {m_webview.reload(); }

signals:
    void pageLoadStarted();
    void pageLoadFinished(bool);
    void pageLoadProgress(int);

protected:
    virtual void resizeEvent (QResizeEvent *event) {
        int w = event->size().width();
        int h = event->size().height();
        m_webview.setGeometry (QRect(0,0,w,h));
    }

protected slots:
    void loadProgress(int);

private:
     QGraphicsWebView m_webview;
     int m_currentProgress;

};

#endif /* BROWSERVIEW_H */
