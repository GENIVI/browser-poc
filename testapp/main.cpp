#include "widget.h"
#include <QApplication>

#include <QDBusMetaType>

#include "../browserdefs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDBusRegisterMetaType<conn::brw::ERROR_IDS>();
    qDBusRegisterMetaType<conn::brw::BOOKMARK_SORT_TYPE>();

    Widget w;
    w.setGeometry(0,0,600,400);
    w.show();
    

    return a.exec();
}
