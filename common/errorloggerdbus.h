#ifndef ERRRORLOGGERDBUS_H
#define ERRRORLOGGERDBUS_H

#include <QObject>
#include "../browser/errorlogger.h"
#include "browserdefs.h"
#include "ierrorlogger_interface.h"

class ErrorLoggerDbus : public QObject
{
    Q_OBJECT

public:
    explicit ErrorLoggerDbus(QObject *parent = 0);

    Q_INVOKABLE uint getItemsCount(qlonglong, qlonglong);
    Q_INVOKABLE conn::brw::ErrorItemList getItems(qlonglong timeFrom,
                                           qlonglong timeTo,
                                           conn::brw::ERROR_SORT_TYPE type,
                                           uint startIndex,
                                           uint itemsCount);

    Q_INVOKABLE void connectdbussession(QString id);

signals:
    void onNewErrorItem(conn::brw::ErrorItem);
    void onErrorListChanged();

private:
    QString m_instanceId;
    void registertypes();
    conn::brw::IErrorLogger *m_errorlogger;
};



#endif /* ERRRORLOGGERDBUS_H */
