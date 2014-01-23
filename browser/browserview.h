#ifndef BROWSERVIEW_H
#define BROWSERVIEW_H

#include <QGraphicsWebView>
#include <QGraphicsView>
#include <QResizeEvent>

class BrowserView : public QGraphicsView
{
     Q_OBJECT
public:
    BrowserView();
    enum ScrollDirection {
        SCROLLDIRECTION_UP,
        SCROLLDIRECTION_DOWN,
        SCROLLDIRECTION_LEFT,
        SCROLLDIRECTION_RIGHT,
        SCROLLDIRECTION_INVALID
    };

    enum ScrollType {
        SCROLLTYPE_SINGLESTEP,
        SCROLLTYPE_PAGESTEP,
        SCROLLTYPE_INVALID
    };
    bool load(const QString &a_Url);
    int getProgress() { return m_currentProgress; }
    QString getURL() { return m_webview.url().toString(); }
    const QString getTitle() { return m_webview.title(); }
    void goBack() { m_webview.back(); }
    void goForward() { m_webview.forward(); }
    void pageReload() { m_webview.reload(); }
    void pageStop() { m_webview.stop(); }
    void scroll (BrowserView::ScrollDirection dir, BrowserView::ScrollType type);
    void inputText (QString input);

signals:
    void pageLoadStarted();
    void pageLoadFinished(bool);
    void pageLoadProgress(int);

protected:
    virtual void resizeEvent (QResizeEvent *event);

protected slots:
    void loadProgress(int);

private:
     QGraphicsWebView m_webview;
     int m_currentProgress;

};

#endif /* BROWSERVIEW_H */
