#include "bookmarkmanager.h"
#include <QDebug>

bookmarkmanager::bookmarkmanager(QObject *parent) :
    QObject(parent)
{
    qDebug() << "bookmarkmanager initialize";
}

ERROR_IDS bookmarkmanager::addItem() {
    qDebug() << "bookmarkmanager::addItem";
    return EID_NOT_IMPLEMENTED;
}

ERROR_IDS bookmarkmanager::deleteAllItems(int type) {
    qDebug() << "bookmarkmanager::deleteAllItems " << type;
    return EID_NOT_IMPLEMENTED;
}

ERROR_IDS bookmarkmanager::deleteItem(int uid) {
    qDebug() << "bookmarkmanager::deleteItem " << uid;
    return EID_NOT_IMPLEMENTED;
}

ERROR_IDS bookmarkmanager::getItems(const QString &path, int type, uint index, uint count) {
    qDebug() << "bookmarkmanager::getItems " << path << type << index << count;
    return EID_NOT_IMPLEMENTED;
}
