CONFIG += qtestlib debug qt
TEMPLATE = app
TARGET = errorloggerdbus-tests
INCLUDEPATH += . ../../../common/
QT += dbus webkitwidgets

my_dbus_interfaces.files += ../../../common/IErrorLogger.xml
my_dbus_interfaces.header_flags = -l errorlogger -i ../../../common/browserdefs.h -i ../../errorlogger.h
DBUS_INTERFACES += my_dbus_interfaces

dbus_adaptors.files += ../../../common/IErrorLogger.xml
dbus_adaptors.header_flags = -l errorlogger -i ../../../common/browserdefs.h -i ../../errorlogger.h
DBUS_ADAPTORS += dbus_adaptors

# Input
HEADERS += testerrorloggerdbus.h ../../../common/errorloggerdbus.h ../../errorlogger.h
SOURCES += testerrorloggerdbus.cpp ../../../common/errorloggerdbus.cpp ../../errorlogger.cpp
