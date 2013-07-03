#include "bookmarkmanager.h"
#include <QDebug>

bookmarkmanager::bookmarkmanager(QObject *parent) :
    QObject(parent)
{
    qDebug() << "bookmarkmanager initialize";
}

void bookmarkmanager::addItem() {
    qDebug() << "bookmarkmanager::addItem";
}

void bookmarkmanager::deleteAllItems(int type) {
    qDebug() << "bookmarkmanager::deleteAllItems " << type;
}

void bookmarkmanager::deleteItem(int uid) {
    qDebug() << "bookmarkmanager::deleteItem " << uid;
}

void bookmarkmanager::getItems(const QString &path, int type, uint index, uint count) {
    qDebug() << "bookmarkmanager::getItems " << path << type << index << count;
}
