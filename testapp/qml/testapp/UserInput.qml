import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    GroupBox {
        id: groupuserinput
        title: "inputText(conn::brw::DIALOG_RESULT a_eResult, const QString &a_strInputValue)"
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 30

        TextField {
            id: inputstring
            width: 400
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
        }
        ComboBox {
            id: combo
            width: 70
            height: inputstring.height
            model: [ "OK", "Cancel" ]
            anchors.top: inputstring.top
            anchors.left: inputstring.right
            anchors.leftMargin: 30
        }
        Button {
            width: 130
            height: inputstring.height
            anchors.top: inputstring.top
            anchors.left: combo.right
            anchors.leftMargin: 30
            text: "Send"
        }
    }
}
