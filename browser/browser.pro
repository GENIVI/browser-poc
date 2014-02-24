
QT += dbus webkitwidgets
CONFIG += debug qt

my_dbus_cachemanager_adaptors.files += ../common/ICacheManager.xml
my_dbus_cachemanager_adaptors.header_flags = -i cachemanager.h -i ../common/browserdefs.h -l cachemanager
my_dbus_cachemanager_adaptors.source_flags = -l cachemanager

my_dbus_errorlogger_adaptors.files += ../common/IErrorLogger.xml
my_dbus_errorlogger_adaptors.header_flags = -i errorlogger.h -i ../common/browserdefs.h -l errorlogger
my_dbus_errorlogger_adaptors.source_flags = -l errorlogger

my_dbus_bookmark_adaptors.files += ../common/IBookmarkManager.xml
my_dbus_bookmark_adaptors.header_flags = -i bookmarkmanager.h -i ../common/browserdefs.h -l bookmarkmanager
my_dbus_bookmark_adaptors.source_flags = -l bookmarkmanager

my_dbus_userinput_adaptors.files += ../common/IUserInput.xml
my_dbus_userinput_adaptors.header_flags = -i ../common/browserdefs.h -i userinput.h -l userinput
my_dbus_userinput_adaptors.source_flags = -l userinput

my_dbus_webpagewindow_adaptors.files += ../common/IWebPageWindow.xml
my_dbus_webpagewindow_adaptors.header_flags = -i webpagewindow.h -i ../common/browserdefs.h -l webpagewindow
my_dbus_webpagewindow_adaptors.source_flags = -l webpagewindow

my_dbus_browser_adaptors.files += ../common/IBrowser.xml
my_dbus_browser_adaptors.header_flags = -i browser.h -i ../common/browserdefs.h -l browser
my_dbus_browser_adaptors.source_flags = -l browser

my_dbus_networkmanager_adaptors.files += ../common/INetworkManager.xml
my_dbus_networkmanager_adaptors.header_flags = -i networkmanager.h -i ../common/browserdefs.h -l networkmanager
my_dbus_networkmanager_adaptors.source_flags = -l networkmanager

DBUS_ADAPTORS += my_dbus_bookmark_adaptors \
                 my_dbus_cachemanager_adaptors \
                 my_dbus_userinput_adaptors \
                 my_dbus_webpagewindow_adaptors \
                 my_dbus_browser_adaptors \
                 my_dbus_errorlogger_adaptors \
                 my_dbus_networkmanager_adaptors

SOURCES += main.cpp \
    bookmarkmanager.cpp \
    userinput.cpp \
    webpagewindow.cpp \
    browser.cpp \
    browserhelper.cpp \
    browserview.cpp \
    browserconfig.cpp \
    cachemanager.cpp \
    errorlogger.cpp \
    browserpage.cpp \
    networkmanager.cpp \
    ../common/bookmark.cpp \

HEADERS += \
    bookmarkmanager.h \
    userinput.h \
    webpagewindow.h \
    browser.h \
    browserhelper.h \
    browserview.h \
    browserconfig.h \
    cachemanager.h \
    errorlogger.h \
    browserpage.h \
    networkmanager.h \
    ../common/bookmark.h \
    ../common/browserdefs.h \

# Generation of the adaptor doesn't trigger properly, so this is a temp fix
system("$$[QT_INSTALL_PREFIX]/bin/qdbusxml2cpp -i cachemanager.h\
                                               -i ../common/browserdefs.h\
                                               -l cachemanager\
                                               -a icachemanager_adaptor.h:\
                                               ../common/ICacheManager.xml")

system("$$[QT_INSTALL_PREFIX]/bin/qdbusxml2cpp -i errorlogger.h\
                                               -i ../common/browserdefs.h\
                                               -l errorlogger\
                                               -a ierrorlogger_adaptor\
                                               ../common/IErrorLogger.xml")

system("$$[QT_INSTALL_PREFIX]/bin/qdbusxml2cpp -i networkmanager.h\
                                               -i ../common/browserdefs.h\
                                               -l networkmanager\
                                               -a inetworkmanager_adaptor\
                                               ../common/INetworkManager.xml")
