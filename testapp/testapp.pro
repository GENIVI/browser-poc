#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T15:54:07
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testapp
TEMPLATE = app

my_dbus_adaptors.files = ../IBookmarkManager.xml
my_dbus_adaptors.header_flags = -i ../browserdefs.h
DBUS_INTERFACES += my_dbus_adaptors

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
        ../browserdefs.h
