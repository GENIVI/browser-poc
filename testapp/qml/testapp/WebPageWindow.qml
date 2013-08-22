import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    GroupBox {
        id: groupcontrolbuttons
        title: "back()/forward()/reload()/stop()    "
        width: 4 * 130 + 3 * 20 + 3 * 10
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 30

        Button {
            id: buttonback
            width: 130
            height: 50
            text: "Back"
            anchors.left: parent.left
            anchors.leftMargin: 10
            onClicked: browserinterface.goBack()
        }
        Button {
            id: buttonforward
            width: 130
            height: 50
            anchors.top: buttonback.top
            anchors.left: buttonback.right
            anchors.leftMargin: 20
            text: "Forward"
            onClicked: browserinterface.goForward()
        }
        Button {
            id: buttonreload
            width: 130
            height: 50
            anchors.top: buttonback.top
            anchors.left: buttonforward.right
            anchors.leftMargin: 20
            text: "Reload"
            onClicked: browserinterface.reload()
        }
        Button {
            id: buttonstop
            width: 130
            height: 50
            anchors.top: buttonback.top
            anchors.left: buttonreload.right
            anchors.leftMargin: 20
            text: "Stop"
            onClicked: browserinterface.stop()
        }
    }

    GroupBox {
        id: groupload
        title: "load(const QString &a_Url)"
        width: 400 + 130 + 20 + 30
        anchors.top: groupcontrolbuttons.bottom
        anchors.topMargin: 10
        anchors.left: groupcontrolbuttons.left

        TextField {
            id: inputfieldurl
            width: 400
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
            text: "http://"
        }
        Button {
            width: 130
            height: inputfieldurl.height
            anchors.top: inputfieldurl.top
            anchors.left: inputfieldurl.right
            anchors.leftMargin: 20
            text: "Load Url"
            onClicked: browserinterface.loadurl(inputfieldurl.text)
        }
    }

    GroupBox {
        id: groupsetvisible
        title: "setVisible(bool a_bVisible)"
        width: 70 + 130 + 20 + 30
        anchors.top: groupload.bottom
        anchors.topMargin: 10
        anchors.left: groupload.left

        ComboBox {
            id: combo
            width: 70
            height: 50
            model: [ "True", "False" ]
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
        Button {
            width: 130
            height: combo.height
            anchors.top: combo.top
            anchors.left: combo.right
            anchors.leftMargin: 20
            text: "Set Visible"
            onClicked: {
                if(combo.currentText == "True")
                    browserinterface.setVisible(true)
                else
                    browserinterface.setVisible(false)
            }
        }
    }

    GroupBox {
        id: groupcontrolbuttons2
        title: "getVisible()/getGeometry()/getContentSize()/getBrowserActionsState()"
        width: 4 * 130 + 3 * 20 + 30
        anchors.top: groupsetvisible.bottom
        anchors.topMargin: 10
        anchors.left: groupsetvisible.left

        Button {
            id: buttongetvisible
            width: 130
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: "Get Visible"
            onClicked: browserinterface.getVisible()
        }

        Button {
            id: buttongetgeometry
            width: 130
            height: 50
            anchors.top: buttongetvisible.top
            anchors.left: buttongetvisible.right
            anchors.leftMargin: 20
            text: "Get Geometry"
            onClicked: browserinterface.getGeometry()
        }

        Button {
            id: buttongetcontentsize
            width: 130
            height: buttongetgeometry.height
            anchors.top: buttongetgeometry.top
            anchors.left: buttongetgeometry.right
            anchors.leftMargin: 20
            text: "Get ContentSize"
        }

        Button {
            width: 130
            height: buttongetgeometry.height
            anchors.top: buttongetgeometry.top
            anchors.left: buttongetcontentsize.right
            anchors.leftMargin: 20
            text: "Get Browser ActionState"
        }
    }

    GroupBox {
        id: groupsetgeometry
        title: "setGeometry(conn::brw::Rect & a_sRect)"
        width: 4 * 50 + 130 + 4 * 20 + 30
        anchors.top: groupcontrolbuttons2.bottom
        anchors.topMargin: 10
        anchors.left: groupcontrolbuttons2.left

        TextField {
            id: inputfieldx
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
            maximumLength: 3
            inputMask: "999"
            text: "0"
        }
        TextField {
            id: inputfieldy
            width: 50
            height: inputfieldx.height
            anchors.top: inputfieldx.top
            anchors.left: inputfieldx.right
            anchors.leftMargin: 20
            font.pixelSize: 20
            maximumLength: 3
            inputMask: "999"
            text: "0"
        }
        TextField {
            id: inputfieldwidth
            width: 50
            height: inputfieldx.height
            anchors.top: inputfieldx.top
            anchors.left: inputfieldy.right
            anchors.leftMargin: 20
            font.pixelSize: 20
            maximumLength: 3
            inputMask: "999"
            text: "800"
        }
        TextField {
            id: inputfieldheight
            width: 50
            height: inputfieldx.height
            anchors.top: inputfieldx.top
            anchors.left: inputfieldwidth.right
            anchors.leftMargin: 20
            font.pixelSize: 20
            maximumLength: 3
            inputMask: "999"
            text: "520"
        }
        Button {
            width: 130
            height: inputfieldx.height
            anchors.top: inputfieldx.top
            anchors.left: inputfieldheight.right
            anchors.leftMargin: 20
            text: "Set Geometry"
            onClicked: browserinterface.setGeometry(inputfieldx.text, inputfieldy.text, inputfieldwidth.text, inputfieldheight.text)
        }
    }

    Text {
        anchors.top: groupsetgeometry.bottom
        anchors.topMargin: 10
        anchors.left: groupsetgeometry.left
        text: "scrolling to be done"
        font.pixelSize: 20
    }
}


