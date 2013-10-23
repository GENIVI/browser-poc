import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    GroupBox {
        id: groupuserinput
        title: "inputText(conn::brw::DIALOG_RESULT a_eResult, const QString &a_strInputValue)"
        width: 400 + 70 + 130 + 70
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 30

        TextField {
            id: inputstring
            width: 400
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 16
        }
        ComboBox {
            id: combo
            width: 70
            height: inputstring.height
            model: [ "OK", "Cancel" ]
            anchors.top: inputstring.top
            anchors.left: inputstring.right
            anchors.leftMargin: 20
        }
        Text {
            text: "Dialog result"
            anchors.top: combo.bottom
            anchors.left: combo.left
        }
        Button {
            width: 130
            height: inputstring.height
            anchors.top: inputstring.top
            anchors.left: combo.right
            anchors.leftMargin: 20
            text: "Send"
            onClicked: browserinterface.inputText(combo.currentIndex, inputstring.text)
        }
    }
}
