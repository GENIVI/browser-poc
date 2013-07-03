#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include <QObject>

class bookmarkmanager : public QObject
{
    Q_OBJECT
public:
    explicit bookmarkmanager(QObject *parent = 0);
    
signals:
    
public Q_SLOTS:
    void addItem();
    void deleteAllItems(int a_i32BookmarkItemType);
    void deleteItem(int a_i32Uid);
    void getItems(const QString &a_strParentFolderPath, int a_i32BookmarkType, uint a_u32StartIndex, uint a_u32ItemsCount);
    
};

#endif // BOOKMARKMANAGER_H
