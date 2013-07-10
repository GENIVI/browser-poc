#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include <QObject>
#include <QDebug>

#include "../browserdefs.h"



class bookmarkmanager : public QObject
{
    Q_OBJECT

public:
    explicit bookmarkmanager(QObject *parent = 0);
    

signals:
    
public Q_SLOTS:
    conn::brw::ERROR_IDS addItem();
    conn::brw::ERROR_IDS deleteAllItems(int a_i32BookmarkItemType);
    conn::brw::ERROR_IDS deleteItem(int a_i32Uid);
    conn::brw::ERROR_IDS getItems(const QString &a_strParentFolderPath, int a_i32BookmarkType, uint a_u32StartIndex, uint a_u32ItemsCount);
    
};

#endif // BOOKMARKMANAGER_H
