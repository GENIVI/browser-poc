#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T15:54:07
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testapp
TEMPLATE = app


DBUS_INTERFACES += ../IBookmarkManager.xml

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
        ../browserdefs.h
