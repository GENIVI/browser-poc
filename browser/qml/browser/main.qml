import QtQuick 2.0
//import QtWebKit 3.0

Rectangle {
    width: 360
    height: 360
    color: "blue"
    Text {
        text: qsTr("Hello World")
        font.pixelSize: 20
        color: "white"
        anchors.centerIn: parent
    }

//    WebView {
//        anchors.fill: parent
////        anchors.margins: 10
//        url: "http://www.pelagicore.com"
//    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
