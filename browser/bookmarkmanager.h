#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include <QObject>

#include <QDebug>


#include <QDBusArgument>

enum ERROR_IDS {
            EID_NO_ERROR,
            EID_ALREADY_EXIST,
            EID_GENERAL_ERROR,
            EID_NOT_IMPLEMENTED,
            EID_NULL_POINTER,
            EID_INVALID_STATE,
            EID_MAX_NUMBER_REACHED,
            EID_INVALID_ARGUMENT,
            EID_NOT_EXISTS,
            EID_DB_ITEM_NOT_EXISTS,
            EID_DB_ITEM_ALREADY_EXISTS,
            EID_DB_CLOSED_HANDLE,
            EID_DB_QUERY_FAILS,
            EID_DB_EXEC_FAILS,
            EID_DB_FILE_EXISTS,
            EID_DB_DISK_OUT_OF_SPACE,
            EID_DB_NO_PERMISSION,
            EID_FILESYSTEM_ERROR // TODO added
        };


inline const QDBusArgument &operator>>(const QDBusArgument &argument, ERROR_IDS test)
{
    qDebug() << "CCCC";
argument.beginStructure();
argument >> test;
argument.endStructure();
return argument;
}

inline QDBusArgument &operator<<(QDBusArgument &argument, const ERROR_IDS test)
{
    qDebug() << "DDDD " << test << " " << (int)test;
argument.beginStructure();
argument << (int)test;
argument.endStructure();
return argument;
}

class bookmarkmanager : public QObject
{
    Q_OBJECT
//    Q_ENUMS(ErrorCodes)

public:
    explicit bookmarkmanager(QObject *parent = 0);
    

signals:
    
public Q_SLOTS:
    ERROR_IDS addItem();
    ERROR_IDS deleteAllItems(int a_i32BookmarkItemType);
    ERROR_IDS deleteItem(int a_i32Uid);
    ERROR_IDS getItems(const QString &a_strParentFolderPath, int a_i32BookmarkType, uint a_u32StartIndex, uint a_u32ItemsCount);
    
};

Q_DECLARE_METATYPE(ERROR_IDS)

#endif // BOOKMARKMANAGER_H
