#include "widget.h"

#include <QVBoxLayout>
#include <QPushButton>

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    bookmark = new conn::brw::IBookmarkManager("conn.brw.IBookmarkManager", "/bookmarkmanager",
                           QDBusConnection::sessionBus(), this);

    QPushButton *b1 = new QPushButton("AddItem");
    b1->setFixedHeight(70);
    QPushButton *b2 = new QPushButton("DeleteItem");
    b2->setFixedHeight(70);
    QPushButton *b3 = new QPushButton("deleteAllItems");
    b3->setFixedHeight(70);
    QPushButton *b4 = new QPushButton("getItems");
    b4->setFixedHeight(70);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(b1);
    layout->addWidget(b2);
    layout->addWidget(b3);
    layout->addWidget(b4);

    connect(b1, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(b2, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(b3, SIGNAL(clicked()), this, SLOT(deleteAllItems()));
    connect(b4, SIGNAL(clicked()), this, SLOT(getItems()));
}

Widget::~Widget()
{   
}


void Widget::addItem() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->addItem();
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }

    // QDBusPendingCallWatcher ???
}

void Widget::deleteItem() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteItem(1);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void Widget::deleteAllItems() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->deleteAllItems(1);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}

void Widget::getItems() {
    qDebug() << __PRETTY_FUNCTION__;

    QDBusPendingReply<conn::brw::ERROR_IDS> reply = bookmark->getItems("hallo", 1, 1, 1);
    reply.waitForFinished();
    if(reply.isValid()) {
        conn::brw::ERROR_IDS ret = reply.value();
        qDebug() << "reply " << ret;
    } else {
        QDBusError error = reply.error();
        qDebug() << "ERROR " << error.name() << error.message();
    }
}
