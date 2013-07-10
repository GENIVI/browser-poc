#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QtDBus/QDBusConnection>
#include <QDBusMetaType>

#include "bookmarkmanager.h"
#include "ibookmarkmanager_adaptor.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/browser/main.qml"));
    viewer.showExpanded();

    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();

    bookmarkmanager *bm = new bookmarkmanager();

    new IBookmarkManagerAdaptor(bm);
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerService("conn.brw.IBookmarkManager");
    connection.registerObject("/bookmarkmanager", bm);

    return app.exec();
}
