import QtQuick 2.0

Item {
    id: root

    property alias imagesource: icon.source
    property alias color: rect.color
    signal buttonClicked()

    height: 80
    width: 50

    Rectangle {
        id: rect
        height: parent.height
        width: parent.width
        color: "darkgray"
        radius: 10
        border.color: "black"
        border.width: 2
        Image {
            id: icon
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: root.buttonClicked()
            onPressed: parent.color = "lightblue"
            onReleased: parent.color = "darkgray"
        }
    }
}
