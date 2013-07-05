#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "bookmarkmanager.h"
#include <QtDBus/QDBusConnection>
#include "ibookmarkmanager_adaptor.h"


#include <QDBusMetaType>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qDBusRegisterMetaType<ERROR_IDS>();

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/browser/main.qml"));
    viewer.showExpanded();

    bookmarkmanager *bm = new bookmarkmanager();

    new IBookmarkManagerAdaptor(bm);
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerService("conn.brw.IBookmarkManager");
    connection.registerObject("/bookmarkmanager", bm);


    return app.exec();
}
