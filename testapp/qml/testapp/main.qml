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

        Rectangle {
            width: parent.width
            height: 2
            color: "black"
            anchors.bottom: parent.bottom
        }
        Text {
            id: instancetxt
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Instance Id:")
        }
        TextField {
            id: inputstring
            width: 30
            height: 30
            text: "1"
            font.pixelSize: 14
            anchors.left: instancetxt.right
            anchors.leftMargin: 3
            anchors.verticalCenter: parent.verticalCenter
        }
        Button {
            id: connectbtn
            width: 70
            height: inputstring.height
            anchors.top: inputstring.top
            anchors.left: inputstring.right
            anchors.leftMargin: 20
            text: "Connect"
            onClicked: browserinterface.connectdbussession(inputstring.text)
        }
        Component {
            id: hallo
            BookmarkManager{}
        }

        Text {
            id: tabs
            anchors.left: connectbtn.right
            anchors.leftMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Tabs:")
            visible: browserinterface.connected
        }
        Button {
            id: tab1
            width: 30
            height: width
            anchors.left: tabs.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "1"
            onClicked: browserinterface.selectTab(1)
            visible: browserinterface.connected
        }
        Button {
            id: tab2
            width: 30
            height: width
            anchors.left: tab1.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "2"
            onClicked: browserinterface.selectTab(2)
            visible: browserinterface.connected
        }
        Button {
            id: tab3
            width: 30
            height: width
            anchors.left: tab2.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "3"
            onClicked: browserinterface.selectTab(3)
            visible: browserinterface.connected
        }
        Button {
            id: tab4
            width: 30
            height: width
            anchors.left: tab3.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "4"
            onClicked: browserinterface.selectTab(4)
            visible: browserinterface.connected
        }
    }

    TabView {
        id: tabview
        anchors.top: header.bottom
        anchors.topMargin: 3
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        visible: browserinterface.connected

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
            id: userinput
            title: "IUserInput"
            anchors.fill: parent
            clip: true
            UserInput {}
        }
        Tab {
            id: bookmarks
            title: "IBookmarkManager"
            anchors.fill: parent
            clip: true
            BookmarkManager {}
        }
    }
}
