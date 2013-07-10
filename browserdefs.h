#ifndef BROWSERDEFS_H
#define BROWSERDEFS_H

#include <QDBusArgument>

namespace conn {
    namespace brw {

    /*!
        * Browser errors definition.

        EID_NO_ERROR - No error
        EID_ALREADY_EXIST - Object already exists. It does not mean always an error. The browser could return EID_ALREADY_EXIST as info and provides required access data.
        EID_NOT_EXISTS - Object not exists. By the delete operation this error code is treated as a info status.
        EID_GENERAL_ERROR - Situation in which programmer did not know what to do
        EID_NOT_IMPLEMENTED - Method, functionality not implemented
        EID_NULL_POINTER - Null pointer
        EID_INVALID_STATE - The system or component is not ready execute the requested operation.
        EID_MAX_NUMBER_REACHED - Maximum number of records is reached.
        EID_INVALID_ARGUMENT - Invalid argument
        EID_DB_ITEM_NOT_EXISTS - Item does not exists in database
        EID_DB_ITEM_ALREADY_EXISTS - Item already exists in database
        EID_DB_CLOSED_HANDLE - Handle to database is closed
        EID_DB_QUERY_FAILS - Prepare of query fails
        EID_DB_EXEC_FAILS - Execute of query on database fails
        EID_DB_FILE_EXISTS - DB cannot create file on drive because file already exists
        EID_DB_DISK_OUT_OF_SPACE - DB cannot create file on drive because there is not enough space
        EID_DB_NO_PERMISSION - DB cannot write to file - lack of permission
        */
    //## type ERROR_IDS
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

    inline const QDBusArgument &operator>>(const QDBusArgument &argument, conn::brw::ERROR_IDS &errorid)
    {
        qDebug() << __PRETTY_FUNCTION__;
        int i;
        argument.beginStructure();
        argument >> i;
        errorid = static_cast<conn::brw::ERROR_IDS>(i);
        argument.endStructure();
        return argument;
    }

    inline QDBusArgument &operator<<(QDBusArgument &argument, const conn::brw::ERROR_IDS &errorid)
    {
        qDebug() << __PRETTY_FUNCTION__;
        argument.beginStructure();
        argument << static_cast<int>(errorid);
        argument.endStructure();
        return argument;
    }

    }
}

Q_DECLARE_METATYPE(conn::brw::ERROR_IDS)

#endif // BROWSERDEFS_H
