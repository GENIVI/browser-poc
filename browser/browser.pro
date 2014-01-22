
QT += dbus declarative webkitwidgets
CONFIG += qt debug

my_dbus_bookmark_adaptors.files += ../common/IBookmarkManager.xml
my_dbus_bookmark_adaptors.header_flags = -i bookmarkmanager.h -i ../common/browserdefs.h -l bookmarkmanager
my_dbus_bookmark_adaptors.source_flags = -l bookmarkmanager

my_dbus_userinput_adaptors.files += ../common/IUserInput.xml
my_dbus_userinput_adaptors.header_flags = -i ../common/browserdefs.h

my_dbus_webpagewindow_adaptors.files += ../common/IWebPageWindow.xml
my_dbus_webpagewindow_adaptors.header_flags = -i webpagewindow.h -i ../common/browserdefs.h -l webpagewindow
my_dbus_webpagewindow_adaptors.source_flags = -l webpagewindow

my_dbus_browser_adaptors.files += ../common/IBrowser.xml
my_dbus_browser_adaptors.header_flags = -i browser.h -i ../common/browserdefs.h -l browser
my_dbus_browser_adaptors.source_flags = -l browser

DBUS_ADAPTORS += my_dbus_bookmark_adaptors my_dbus_userinput_adaptors my_dbus_webpagewindow_adaptors my_dbus_browser_adaptors

SOURCES += main.cpp \
    bookmarkmanager.cpp \
    userinput.cpp \
    webpagewindow.cpp \
    browser.cpp \
    browserhelper.cpp \
    browserview.cpp \
    ../common/bookmark.cpp \

HEADERS += \
    bookmarkmanager.h \
    userinput.h \
    webpagewindow.h \
    browser.h \
    browserhelper.h \
    browserview.h \
    ../common/bookmark.h \
    ../common/browserdefs.h \

OTHER_FILES += \
    qml/browser/main.qml \

