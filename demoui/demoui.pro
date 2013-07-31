# Add more folders to ship with the application, here
folder_01.source = qml/demoui
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =


my_dbus_interfaces.files += ../IBookmarkManager.xml \
    ../IUserInput.xml \
    ../IWebPageWindow.xml \
    ../IBrowser.xml
my_dbus_interfaces.header_flags = -i ../common/browserdefs.h
DBUS_INTERFACES += my_dbus_interfaces

QT += core dbus

include(../common/common.pri)

SOURCES += main.cpp \
    browserdbus.cpp

HEADERS += browserdbus.h \

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

