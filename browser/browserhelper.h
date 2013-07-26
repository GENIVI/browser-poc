#ifndef BROWSERHELPER_H
#define BROWSERHELPER_H

#include <QObject>

#include <QQuickItem>

#include "webpagewindow.h"

class browserhelper : public QObject
{
    Q_OBJECT
public:
    explicit browserhelper(QObject *parent = 0);
    
    QQuickItem *item;
signals:
    
public slots:
    void browserreload();
    void browserback();
    void browserforward();
    void browserstop();
    void browserloadurl(QString url);

    void test();

private:
    webpagewindow *wpw;

    
};

#endif // BROWSERHELPER_H
