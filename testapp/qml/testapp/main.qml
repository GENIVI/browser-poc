import QtQuick 2.0
import QtQuick.Controls 1.0
import browserdbusinterface 1.0

ApplicationWindow {
    id: root
    title: "Genivi Browser PoC test application"
    width: 800
    height: 700
    color: "gray"

    BrowserInterface {
        id: browserinterface
    }
    TabView {
        anchors.fill: parent

        Tab {
            id: browser
            title: "IBrowser"
            anchors.fill: parent
            clip: true
            Browser {}
        }
        Tab {
            id: webpage
            title: "IWebPageWindow"
            anchors.fill: parent
            clip: true
            WebPageWindow {}
        }
        Tab {
            id: bookmarks
            title: "IBookmarkManager"
            anchors.fill: parent
            clip: true
            BookmarkManager {}
        }
        Tab {
            id: userinput
            title: "IUserInput"
            anchors.fill: parent
            clip: true
            UserInput {}
        }
    }

    Component.onCompleted: browserinterface.connectdbussession("1")
}
