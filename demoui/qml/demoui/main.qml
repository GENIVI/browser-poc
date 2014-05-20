import QtQuick 2.0
import browserdbusinterface 1.0

Item {
    id: root
    width: 1024
    height: 768

    signal bookmarksopen(bool open)

    Item {
        id: privateMem
        property bool bookmarklistopen: false
    }

    Component.onCompleted: {
        browserinterface.connectdbussession("1")
        browserinterface.createPageWindow(1, 0, 80, 1024, 688);
        browserinterface.reload() // show initial url
    }

    Item {
        id: controls
        y: 0
        width: parent.width
        height: parent.height

        BrowserInterface {
            id: browserinterface
        }

        focus: true
        Keys.onDownPressed: browserinterface.goDown(0)
        Keys.onUpPressed: browserinterface.goUp(0)
        Keys.onLeftPressed: browserinterface.goLeft(0)
        Keys.onRightPressed: browserinterface.goRight(0)
        Keys.onSpacePressed: browserinterface.goDown(1)
        Keys.onTabPressed: browserinterface.goUp(1)

        Rectangle {
            id: bg
            width: parent.width
            color: "transparent"
            height: 80
        }
        Button {
            id: backbutton
            imagesource: "../../images/go-previous-view.png"
            onButtonClicked: browserinterface.goBack()
        }
        Button {
            id: forwardbutton
            anchors.left: backbutton.right
            anchors.leftMargin: 1
            imagesource: "../../images/go-next-view.png"
            onButtonClicked: browserinterface.goForward()
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
                        privateMem.bookmarklistopen = false
                        root.bookmarksopen(privateMem.bookmarklistopen)
                        browserinterface.loadurl(text)
                    }

                }
                Rectangle {
                    id: progressbar
                    height: 5
                    width: (parent.width - reloadbutton.width) * browserinterface.progress / 100
                    color: "lightblue"
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    visible: browserinterface.pageloading
                }
                Rectangle {
                    id: reloadbutton
                    height: parent.height
                    width: parent.height
                    color: "lightgray"
                    anchors.right: parent.right
                    Image {
                        source: browserinterface.pageloading ? "../../images/process-stop.png" : "../../images/view-refresh.png"
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: browserinterface.pageloading ? browserinterface.stop() : browserinterface.reload()
                    }
                }
            }
        }
        Button {
            id: addbookmark
            width: 70
            anchors.right: bookmarks.left
            anchors.rightMargin: 1
            imagesource: "../../images/bookmarks.png"
            onButtonClicked: {
                browserinterface.addBookmark(1, "", browserinterface.title, browserinterface.url, "", "")
            }
        }

        Button {
            id: bookmarks
            width: 70
            anchors.right: parent.right
            imagesource: "../../images/bookmark-new-list.png"
            onButtonClicked: {
                if(privateMem.bookmarklistopen) {
                    bookmarklist.state = ""
                    privateMem.bookmarklistopen = false
                    root.bookmarksopen(privateMem.bookmarklistopen)
                } else {
                    browserinterface.getBookmarks("", 1, 0, 1, 20)
                    bookmarklist.state = "open"
                    privateMem.bookmarklistopen = true
                    root.bookmarksopen(privateMem.bookmarklistopen)
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
                    privateMem.bookmarklistopen = false
                    root.bookmarksopen(privateMem.bookmarklistopen)
                    browserinterface.deleteAllBookmarks(1)
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
                        privateMem.bookmarklistopen = false
                        root.bookmarksopen(privateMem.bookmarklistopen)
                    }
                    onPressed: {
                        bookmarkurl.color = "lightblue"
                        bookmarktitle.color = "lightblue"
                    }
                    onReleased: {
                        bookmarkurl.color = "white"
                        bookmarktitle.color = "white"
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
                        onClicked: browserinterface.deleteBookmark(model.modelData.uid)
                        onPressed: bookmarkdeletebutton.color = "lightblue"
                        onReleased: bookmarkdeletebutton.color = "darkgray"
                    }
                    Rectangle {
                        id: bookmarkdeletebutton
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
        }
    }
}
