#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T15:54:07
#
#-------------------------------------------------

QT       += core gui dbus qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testapp
TEMPLATE = app

my_dbus_interfaces.files += ../common/IBookmarkManager.xml \
    ../common/IUserInput.xml \
    ../common/IWebPageWindow.xml \
    ../common/IBrowser.xml
my_dbus_interfaces.header_flags = -i ../common/browserdefs.h
DBUS_INTERFACES += my_dbus_interfaces

include(../common/common.pri)

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \

OTHER_FILES += \
    qml/testapp/main.qml \
    qml/testapp/UserInput.qml \
    qml/testapp/Browser.qml \
    qml/testapp/BookmarkManager.qml \
    qml/testapp/WebPageWindow.qml

