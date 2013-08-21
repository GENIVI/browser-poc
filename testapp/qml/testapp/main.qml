import QtQuick 2.0
import QtQuick.Controls 1.0

ApplicationWindow {
    id: root
    title: "Genivi Browser PoC test application"
    width: 800
    height: 700
    color: "gray"

    TabView {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50

        Tab {
            id: bookmarks
            title: "IBookmarkManager"
            anchors.fill: parent
            clip: true
            BookmarkManager {}
        }
        Tab {
            id: browser
            title: "IBrowser"
            anchors.fill: parent
            clip: true
            Browser {}
        }
        Tab {
            id: userinput
            title: "IUserInput"
            anchors.fill: parent
            clip: true
            UserInput {}
        }
        Tab {
            id: webpage
            title: "IWebPageWindow"
            anchors.fill: parent
            clip: true
            WebPageWindow {}
        }
    }


}
