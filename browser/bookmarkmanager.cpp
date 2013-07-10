#include "bookmarkmanager.h"
#include <QDebug>

bookmarkmanager::bookmarkmanager(QObject *parent) :
    QObject(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
}

ERROR_IDS bookmarkmanager::addItem() {
    qDebug() << __PRETTY_FUNCTION__;
    return EID_NOT_IMPLEMENTED;
}

ERROR_IDS bookmarkmanager::deleteAllItems(int type) {
    qDebug() << __PRETTY_FUNCTION__ << type;
    return EID_NOT_IMPLEMENTED;
}

ERROR_IDS bookmarkmanager::deleteItem(int uid) {
    qDebug() << __PRETTY_FUNCTION__ << uid;
    return EID_NOT_IMPLEMENTED;
}

ERROR_IDS bookmarkmanager::getItems(const QString &path, int type, uint index, uint count) {
    qDebug() << __PRETTY_FUNCTION__ << path << type << index << count;
    return EID_NOT_IMPLEMENTED;
}
