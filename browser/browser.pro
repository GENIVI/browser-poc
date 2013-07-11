# Add more folders to ship with the application, here
folder_01.source = qml/browser
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += dbus

my_dbus_adaptors.files = ../IBookmarkManager.xml
my_dbus_adaptors.header_flags = -i ../browserdefs.h
DBUS_ADAPTORS += my_dbus_adaptors

SOURCES += main.cpp \
    bookmarkmanager.cpp

HEADERS += \
    bookmarkmanager.h \
    ../browserdefs.h

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

