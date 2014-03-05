import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: item1
    GroupBox {
        id: groupCreateEntry
        anchors.bottom: groupGetErrors.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        title: "Create entry (simple)"

        TextField {
            id: textDescription
            anchors.right: btnCreateEntry.left
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 12
        }

        Button {
            id: btnCreateEntry
            x: -106
            y: 0
            text: "Create entry"
            anchors.top: groupCreateEntry.bottom
            anchors.right: parent.right
        }

        Text {
            id: text1
            x: 0
            y: 27
            text: qsTr("Description")
            anchors.left: parent.left
        anchors.top: textDescription.bottom
        font.pixelSize: 12
    }


    }

    GroupBox {
        id: groupGetErrors
        anchors.topMargin: 0
        anchors.top: groupCreateEntry.bottom
        anchors.bottom: parent.bottom
        title: "Retrieve errors"
        anchors.left: parent.left
        anchors.right: parent.right

    ListModel {
    id: errorsModel;
    }

        ListView {
            id: listErrors
            anchors.bottom: groupErrorsControls.top
            anchors.left: parent.left
            anchors.right: parent.right
model: errorsModel;
        }

        GroupBox {
            id: groupErrorsControls
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            Button {
                id: btnGetErrors
                text: "Get errors"
                anchors.bottom: parent.bottom
                anchors.left: item1.right
                anchors.leftMargin: 8
                anchors.right: parent.right
        onClicked: {
            errorloggerinterface.getItems(0, Math.round(new Date().getTime()), 0, 0, 100);
}
            }
        }
        }

}
