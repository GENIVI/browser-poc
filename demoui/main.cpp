#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QQmlContext>

#include "browserdbus.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;

    browserdbus browserdbushelper;

    QList<QObject*> dataList;
    dataList.append(new DataObject("Genivi", "http://www.genivi.org"));
    dataList.append(new DataObject("Pelagicore", "http://www.pelagicore.com"));
    dataList.append(new DataObject("BMW", "http://bmw.com"));
    dataList.append(new DataObject("XXX", "http://www.xxx.com"));
    dataList.append(new DataObject("YYY", "http://www.y.com"));

    viewer.rootContext()->setContextProperty("bookmarkModel", QVariant::fromValue(dataList));


    viewer.rootContext()->setContextProperty("testbrowser", &browserdbushelper);

    viewer.setMainQmlFile(QStringLiteral("qml/demoui/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
