# Add more folders to ship with the application, here
folder_01.source = qml/browser
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =


QT += dbus

my_dbus_bookmark_adaptors.files += ../IBookmarkManager.xml
my_dbus_bookmark_adaptors.header_flags = -i bookmarkmanager.h -i ../browserdefs.h -l bookmarkmanager
my_dbus_bookmark_adaptors.source_flags = -l bookmarkmanager

my_dbus_userinput_adaptors.files += ../IUserInput.xml
my_dbus_userinput_adaptors.header_flags = -i ../browserdefs.h

my_dbus_webpagewindow_adaptors.files += ../IWebPageWindow.xml
my_dbus_webpagewindow_adaptors.header_flags = -i webpagewindow.h -i ../browserdefs.h -l webpagewindow
my_dbus_webpagewindow_adaptors.source_flags = -l webpagewindow

my_dbus_browser_adaptors.files += ../IBrowser.xml
my_dbus_browser_adaptors.header_flags = -i browser.h -i ../browserdefs.h -l browser
my_dbus_browser_adaptors.source_flags = -l browser

DBUS_ADAPTORS += my_dbus_bookmark_adaptors my_dbus_userinput_adaptors my_dbus_webpagewindow_adaptors my_dbus_browser_adaptors

include(../common/common.pri)

SOURCES += main.cpp \
    bookmarkmanager.cpp \
    userinput.cpp \
    webpagewindow.cpp \
    browser.cpp \
    browserhelper.cpp

HEADERS += \
    bookmarkmanager.h \
    ../browserdefs.h \
    userinput.h \
    webpagewindow.h \
    browser.h \
    browserhelper.h

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

