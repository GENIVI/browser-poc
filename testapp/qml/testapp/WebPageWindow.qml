import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    Button {
        id: buttonback
        width: 130
        height: 50
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        text: "Back"
    }
    Button {
        id: buttonforward
        width: 130
        height: 50
        anchors.top: buttonback.top
        anchors.left: buttonback.right
        anchors.leftMargin: 30
        text: "Forward"
    }
    Button {
        id: buttonreload
        width: 130
        height: 50
        anchors.top: buttonback.top
        anchors.left: buttonforward.right
        anchors.leftMargin: 30
        text: "Reload"
    }
    Button {
        id: buttonstop
        width: 130
        height: 50
        anchors.top: buttonback.top
        anchors.left: buttonreload.right
        anchors.leftMargin: 30
        text: "Stop"
    }

    TextField {
        id: inputfieldurl
        width: 400
        height: 50
        anchors.top: buttonback.bottom
        anchors.topMargin: 30
        anchors.left: buttonback.left
        font.pixelSize: 20
    }
    Button {
        width: 130
        height: inputfieldurl.height
        anchors.top: inputfieldurl.top
        anchors.left: inputfieldurl.right
        anchors.leftMargin: 30
        text: "Load"
    }

    ComboBox {
        id: combo
        width: 70
        height: 50
        model: [ "True", "False" ]
        anchors.top: inputfieldurl.bottom
        anchors.topMargin: 30
        anchors.left: inputfieldurl.left
    }
    Button {
        width: 130
        height: combo.height
        anchors.top: combo.top
        anchors.left: combo.right
        anchors.leftMargin: 30
        text: "setVisible"
    }

    Button {
        id: buttongetgeometry
        width: 130
        height: 50
        anchors.top: combo.bottom
        anchors.topMargin: 30
        anchors.left: combo.left
        text: "getGeometry"
    }

    Button {
        id: buttongetcontentsize
        width: 130
        height: buttongetgeometry.height
        anchors.top: buttongetgeometry.top
        anchors.left: buttongetgeometry.right
        anchors.leftMargin: 30
        text: "getContentSize"
    }

    Button {
        width: 130
        height: buttongetgeometry.height
        anchors.top: buttongetgeometry.top
        anchors.left: buttongetcontentsize.right
        anchors.leftMargin: 30
        text: "getBrowserActionState"
    }

    TextField {
        id: inputfieldx
        width: 50
        height: 50
        anchors.top: buttongetgeometry.bottom
        anchors.topMargin: 30
        anchors.left: buttongetgeometry.left
        font.pixelSize: 20
    }
    TextField {
        id: inputfieldy
        width: 50
        height: inputfieldx.height
        anchors.top: inputfieldx.top
        anchors.left: inputfieldx.right
        anchors.leftMargin: 30
        font.pixelSize: 20
    }
    TextField {
        id: inputfieldwidth
        width: 50
        height: inputfieldx.height
        anchors.top: inputfieldx.top
        anchors.left: inputfieldy.right
        anchors.leftMargin: 30
        font.pixelSize: 20
    }
    TextField {
        id: inputfieldheight
        width: 50
        height: inputfieldx.height
        anchors.top: inputfieldx.top
        anchors.left: inputfieldwidth.right
        anchors.leftMargin: 30
        font.pixelSize: 20
    }
    Button {
        width: 130
        height: inputfieldx.height
        anchors.top: inputfieldx.top
        anchors.left: inputfieldheight.right
        anchors.leftMargin: 30
        text: "setgeometry"
    }

    Text {
        anchors.top: inputfieldx.bottom
        anchors.topMargin: 30
        anchors.left: inputfieldx.left
        text: "scrolling to be done"
        font.pixelSize: 20
    }
}


