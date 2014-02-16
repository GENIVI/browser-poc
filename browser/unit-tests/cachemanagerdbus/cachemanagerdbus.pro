CONFIG += qtestlib debug qt
TEMPLATE = app
TARGET = cachemanagerdbus-tests
INCLUDEPATH += . ../../../common/
QT += dbus webkitwidgets

my_dbus_interfaces.files += ../../../common/ICacheManager.xml
my_dbus_interfaces.header_flags = -i ../../../common/browserdefs.h
DBUS_INTERFACES += my_dbus_interfaces

# Input
HEADERS += testcachemanagerdbus.h ../../../common/cachemanagerdbus.h
SOURCES += testcachemanagerdbus.cpp ../../../common/cachemanagerdbus.cpp
