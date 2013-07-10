#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "ibookmarkmanager_interface.h"

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void addItem();
    void getItems();
    void deleteItem();
    void deleteAllItems();

private:
    ConnBrwIBookmarkManagerInterface *bookmark;
};

#endif // WIDGET_H
