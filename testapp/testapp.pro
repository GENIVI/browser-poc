#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T15:54:07
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testapp
TEMPLATE = app

my_dbus_interfaces.files += ../IBookmarkManager.xml \
    ../IUserInput.xml \
    ../IWebPageWindow.xml \
    ../IBrowser.xml
my_dbus_interfaces.header_flags = -i ../common/browserdefs.h
DBUS_INTERFACES += my_dbus_interfaces

include(../common/common.pri)

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
