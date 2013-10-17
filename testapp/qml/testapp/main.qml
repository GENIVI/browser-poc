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

    Item {
        id: header
        width: parent.width
        height: 40

        TextField {
            id: inputstring
            width: 30
            height: 30
            text: "1"
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 14
        }

        Button {
            width: 80
            height: inputstring.height
            anchors.top: inputstring.top
            anchors.left: inputstring.right
            anchors.leftMargin: 20
            text: "Connect"
            onClicked: browserinterface.connectdbussession(inputstring.text)
        }
    }

    TabView {
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

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
}
