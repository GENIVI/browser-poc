import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    GroupBox {
        id: groupcreate
        title: "createPageWindow(int a_eDeviceId, conn::brw::Rect & a_oGeometry, qlonglong &a_hPageWindowHandle)"
        width: children.width + 250
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 30

        TextField {
            id: deviceidcreate
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
            inputMask: "999"
            text: "1"
        }
        Text {
            text: "Device id"
            anchors.top: deviceidcreate.bottom
            anchors.left: deviceidcreate.left
        }
        SpinBox {
            id: spinbox_x
            width: 50
            height: deviceidcreate.height
            anchors.top: deviceidcreate.top
            anchors.left: deviceidcreate.right
            anchors.leftMargin: 30
            maximumValue: 9999
        }
        Text {
            text: "x"
            anchors.top: spinbox_x.bottom
            anchors.left: spinbox_x.left
        }
        SpinBox {
            id: spinbox_y
            width: 50
            height: spinbox_x.height
            anchors.top: spinbox_x.top
            anchors.left: spinbox_x.right
            anchors.leftMargin: 10
            maximumValue: 9999
        }
        Text {
            text: "y"
            anchors.top: spinbox_y.bottom
            anchors.left: spinbox_y.left
        }
        SpinBox {
            id: spinbox_width
            width: 50
            height: spinbox_y.height
            anchors.top: spinbox_y.top
            anchors.left: spinbox_y.right
            anchors.leftMargin: 10
            value: 800
            maximumValue: 9999
        }
        Text {
            text: "width"
            anchors.top: spinbox_width.bottom
            anchors.left: spinbox_width.left
        }
        SpinBox {
            id: spinbox_height
            width: 50
            height: spinbox_width.height
            anchors.top: spinbox_width.top
            anchors.left: spinbox_width.right
            anchors.leftMargin: 10
            value: 520
            maximumValue: 9999
        }
        Text {
            text: "height"
            anchors.top: spinbox_height.bottom
            anchors.left: spinbox_height.left
        }
        Button {
            id: buttoncreate
            width: 130
            height: spinbox_height.height
            anchors.top: spinbox_height.top
            anchors.left: spinbox_height.right
            anchors.leftMargin: 20
            text: "Create Page Window"
            onClicked: browserinterface.createPageWindow(deviceidcreate.text, spinbox_x.value, spinbox_y.value, spinbox_width.value, spinbox_height.value)
        }
    }

    GroupBox {
        id: groupdestroy
        title: "destroyPageWindow(qlonglong a_hPageWindowHandle)"
        width: 150 + 130 + 60
        anchors.top: groupcreate.bottom
        anchors.topMargin: 20
        anchors.left: groupcreate.left

        TextField {
            id: windowhandledestroy
            width: 150
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
            inputMask: "999999999999"
        }
        Button {
            width: 130
            height: windowhandledestroy.height
            anchors.top: windowhandledestroy.top
            anchors.left: windowhandledestroy.right
            anchors.leftMargin: 30
            text: "Destroy Page Window"
            onClicked: browserinterface.destroyPageWindow(windowhandledestroy.text)
        }
    }

    GroupBox {
        id: groupget
        title: "getPageWindows(conn::brw::ObjectHandleList &a_oPageWindowIds)"
        height: 80
        anchors.top: groupdestroy.bottom
        anchors.topMargin: 20
        anchors.left: groupdestroy.left

        Button {
            id: button
            width: 130
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: "Get Page Window"
        }
    }
}
