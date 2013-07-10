#include "widget.h"
#include <QApplication>

#include <QDBusMetaType>

#include "../browserdefs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDBusRegisterMetaType<ERROR_IDS>();

    Widget w;
    w.setGeometry(0,0,600,400);
    w.show();
    

    return a.exec();
}
