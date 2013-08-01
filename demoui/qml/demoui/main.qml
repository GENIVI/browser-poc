import QtQuick 2.0
import browserdbusinterface 1.0

Item {
    id: root
    width: 800
    height: 600

    BrowserInterface {
        id: browserinterface
    }

    Rectangle {
        id: bg
        width: parent.width
        height: 80
    }

    Rectangle {
        id: backbutton
        height: 80
        width: 50
        color: "darkgray"
        radius: 10
        border.color: "black"
        border.width: 2
        Image {
            source: "../../images/go-previous-view.png"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: browserinterface.goBack()
            onPressed: parent.color = "lightblue"
            onReleased: parent.color = "darkgray"
        }
    }
    Rectangle {
        id: forwardbutton
        height: 80
        width: backbutton.width
        color: "darkgray"
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.left: backbutton.right
        anchors.leftMargin: 1
        Image {
            source: "../../images/go-next-view.png"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: browserinterface.goForward()
            onPressed: parent.color = "lightblue"
            onReleased: parent.color = "darkgray"
        }
    }
    Rectangle {
        id: urlbar
        height: 80
        color: "darkgray"
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.left: forwardbutton.right
        anchors.leftMargin: 1
        anchors.right: addbookmark.left
        anchors.rightMargin: 1
        Rectangle {
            color: "white"
            anchors.fill: parent
            anchors.margins: 20
            TextInput {
                id: txturl
                text: browserinterface.url
                font.pixelSize: 20
                clip: true
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5

                onAccepted: {
                    bookmarklist.state = ""
                    bookmarklistopen = false
                    browserinterface.loadurl(text)
                }
            }
            Rectangle {
                height: parent.height
                width: parent.height
                color: "lightgray"
                anchors.right: parent.right
                Image {
                    source: "../../images/view-refresh.png"
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: browserinterface.reload()
                }
            }
        }
    }
    Rectangle {
        id: addbookmark
        height: 80
        width: 70
        color: "darkgray"
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.right: bookmarks.left
        anchors.rightMargin: 1
        Image {
            source: "../../images/bookmarks.png"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                browserinterface.getCurrentUrlAndTitle()
                browserinterface.addBookmark(browserinterface.url, browserinterface.title)
            }
            onPressed: parent.color = "lightblue"
            onReleased: parent.color = "darkgray"
        }
    }
    property bool bookmarklistopen: false

    Rectangle {
        id: bookmarks
        height: 80
        width: 70
        color: "darkgray"
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.right: parent.right
        Image {
            source: "../../images/bookmark-new-list.png"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(bookmarklistopen) {
                    bookmarklist.state = ""
                    bookmarklistopen = false
                } else {
                    browserinterface.getBookmarks()
                    bookmarklist.state = "open"
                    bookmarklistopen = true
                }
            }
        }
    }
    Rectangle {
        id: bookmarklist
        x: parent.width
        width: 500
        opacity: 0.7
        anchors.top: bookmarks.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        color: "darkgray"
        radius: 10
        border.color: "black"
        border.width: 2
        states: [
            State {
                name: "open"
                PropertyChanges { target: bookmarklist; x: parent.width - bookmarklist.width }
                PropertyChanges { target: bookmarks; color: "lightblue" }
            }
        ]
        Behavior on x {
            NumberAnimation { duration: 500; easing.type: Easing.OutBounce }
        }
    }

    Rectangle {
        id: deleteallbutton
        width: 400
        height: 50
        opacity: 1.0
        color: "red"
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.bottom: bookmarklist.bottom
        anchors.bottomMargin: 5
        anchors.horizontalCenter: bookmarklist.horizontalCenter
        z:1
        Image {
            source: "../../images/task-attention.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 40
        }
        Text {
            text: "Delete all bookmarks"
            color: "white"
            font.pixelSize: 20
            anchors.centerIn: parent
        }
        Image {
            source: "../../images/task-attention.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 40
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                bookmarklist.state = ""
                bookmarklistopen = false
                browserinterface.deleteAllBookmarks()
            }
        }
    }

    ListView {
        id: list

        anchors.top: bookmarklist.top
        anchors.left: bookmarklist.left
        anchors.right: bookmarklist.right
        anchors.bottom: deleteallbutton.top
        anchors.margins: 10
        clip: true
        highlightFollowsCurrentItem: true
        z: 1
        model: browserinterface.bookmarkList

        delegate: Item {
            width: parent.width
            height: 70
            MouseArea {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: deletebutton.right
                anchors.leftMargin: 10
                anchors.right: parent.right
                onClicked: {
                    list.currentIndex = index
                    browserinterface.loadurl(model.modelData.url)
                    bookmarklist.state = ""
                    bookmarklistopen = false
                }
            }
            Image {
                id: deletebutton
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                source: "../../images/list-remove.png"
                MouseArea {
                    anchors.fill: parent
                    anchors.margins: -10
                    onClicked: console.log("delete clicked")
                }
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: -10
                    color: "darkgray"
                    radius: 5
                    z: -1
                }
            }
            Text {
                id: bookmarktitle
                text: model.modelData.title
                color: "white"
                elide: Text.ElideRight
                font.pixelSize: 20
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: deletebutton.right
                anchors.leftMargin: 30
                anchors.right: parent.right
            }
            Text {
                id: bookmarkurl
                text: model.modelData.url
                color: "white"
                elide: Text.ElideRight
                font.pixelSize: 16
                anchors.top: bookmarktitle.bottom
                anchors.topMargin: 5
                anchors.left: bookmarktitle.left
                anchors.right: parent.right
            }

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: 1
                color: "black"
            }

        }

//        highlight: Item {
//            width: list.width
//            height: 70

//            Rectangle {
//                anchors.fill: parent
//                color: "lightblue"
//                radius: 5
//                anchors.left: parent.left
//                anchors.right: parent.right
//                anchors.bottom: parent.bottom
//            }
//        }
    }
}
