import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    GroupBox {
        id: groupcreate
        title: "createPageWindow(int a_eDeviceId, const conn::brw::Rect & a_oGeometry, qlonglong &a_hPageWindowHandle)"
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
        }
        SpinBox {
            id: spinbox_x
            width: 50
            height: deviceidcreate.height
            anchors.top: deviceidcreate.top
            anchors.left: deviceidcreate.right
            anchors.leftMargin: 30
        }
        SpinBox {
            id: spinbox_y
            width: 50
            height: spinbox_x.height
            anchors.top: spinbox_x.top
            anchors.left: spinbox_x.right
            anchors.leftMargin: 10
        }
        SpinBox {
            id: spinbox_width
            width: 50
            height: spinbox_y.height
            anchors.top: spinbox_y.top
            anchors.left: spinbox_y.right
            anchors.leftMargin: 10
        }
        SpinBox {
            id: spinbox_height
            width: 50
            height: spinbox_width.height
            anchors.top: spinbox_width.top
            anchors.left: spinbox_width.right
            anchors.leftMargin: 10
        }
        Button {
            id: buttoncreate
            width: 130
            height: spinbox_height.height
            anchors.top: spinbox_height.top
            anchors.left: spinbox_height.right
            anchors.leftMargin: 20
            text: "Create Page Window"
        }
    }

    GroupBox {
        id: groupdestroy
        title: "destroyPageWindow(qlonglong a_hPageWindowHandle)"
        width: children.width + 250
        anchors.top: groupcreate.bottom
        anchors.topMargin: 20
        anchors.left: groupcreate.left

        TextField {
            id: windowhandledestroy
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
        }
        Button {
            width: 130
            height: windowhandledestroy.height
            anchors.top: windowhandledestroy.top
            anchors.left: windowhandledestroy.right
            anchors.leftMargin: 30
            text: "Destroy Page Window"
        }
    }

    GroupBox {
        id: groupget
        title: "getPageWindows(conn::brw::ObjectHandleList &a_oPageWindowIds)"
        width: children.width + 250
        height: 50
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
