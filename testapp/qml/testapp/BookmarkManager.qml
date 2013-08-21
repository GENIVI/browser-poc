import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    GroupBox {
        id: groupadditem
        title: "addItem(const conn::brw::BookmarkItem & a_oItem)"
        width: children.width + 250
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30

        TextField {
            id: uidadditem
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
            maximumLength: 3
            inputMask: "999"
        }
        TextField {
            id: typeadditem
            width: 50
            height: uidadditem.height
            anchors.top: uidadditem.top
            anchors.left: uidadditem.right
            anchors.leftMargin: 20
            font.pixelSize: 20
            maximumLength: 3
            inputMask: "999"
        }
        TextField {
            id: folderpathadditem
            width: 50
            height: uidadditem.height
            anchors.top: typeadditem.top
            anchors.left: typeadditem.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        TextField {
            id: titleadditem
            width: 50
            height: uidadditem.height
            anchors.top: folderpathadditem.top
            anchors.left: folderpathadditem.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        TextField {
            id: urladditem
            width: 50
            height: uidadditem.height
            anchors.top: titleadditem.top
            anchors.left: titleadditem.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        TextField {
            id: iconpathadditem
            width: 50
            height: uidadditem.height
            anchors.top: urladditem.top
            anchors.left: urladditem.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        TextField {
            id: thumbnailpathadditem
            width: 50
            height: uidadditem.height
            anchors.top: iconpathadditem.top
            anchors.left: iconpathadditem.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        Button {
            width: 130
            height: uidadditem.height
            anchors.top: thumbnailpathadditem.top
            anchors.left: thumbnailpathadditem.right
            anchors.leftMargin: 20
            text: "Add Item"
        }
    }

    GroupBox {
        id: groupdeleteitem
        title: "deleteItem(int a_i32Uid)"
        width: children.width + 200
        anchors.top: groupadditem.bottom
        anchors.topMargin: 10
        anchors.left: groupadditem.left

        TextField {
            id: uiddeleteitem
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
            maximumLength: 3
            inputMask: "999"
        }
        Button {
            width: 130
            height: uiddeleteitem.height
            anchors.top: uiddeleteitem.top
            anchors.left: uiddeleteitem.right
            anchors.leftMargin: 20
            text: "Delete Item"
        }
    }

    GroupBox {
        id: groupdeleteallitem
        title: "deleteAllItems(int a_i32BookmarkItemType)"
        width: children.width + 200
        anchors.top: groupdeleteitem.bottom
        anchors.topMargin: 10
        anchors.left: groupdeleteitem.left

        TextField {
            id: typedeleteall
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
            maximumLength: 3
            inputMask: "999"
        }
        Button {
            width: 130
            height: typedeleteall.height
            anchors.top: typedeleteall.top
            anchors.left: typedeleteall.right
            anchors.leftMargin: 20
            text: "Delete All Items"
        }
    }


    GroupBox {
        id: groupgetitems
        title: "getItems(const QString &a_strParentFolderPath, int a_i32BookmarkType, conn::brw::BOOKMARK_SORT_TYPE a_eSortingOrder, uint a_u32StartIndex, uint a_u32ItemsCount, conn::brw::BookmarkItemList &a_oItems)"
        width: children.width + 200
        anchors.top: groupdeleteallitem.bottom
        anchors.topMargin: 10
        anchors.left: groupdeleteallitem.left

        TextField {
            id: folderpathgetitems
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 20
        }
        TextField {
            id: typegetitems
            width: 50
            height: folderpathgetitems.height
            anchors.top: folderpathgetitems.top
            anchors.left: folderpathgetitems.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        TextField {
            id: sortinggetitems
            width: 50
            height: folderpathgetitems.height
            anchors.top: typegetitems.top
            anchors.left: typegetitems.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        TextField {
            id: startindexgetitems
            width: 50
            height: folderpathgetitems.height
            anchors.top: sortinggetitems.top
            anchors.left: sortinggetitems.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        TextField {
            id: countgetitems
            width: 50
            height: folderpathgetitems.height
            anchors.top: startindexgetitems.top
            anchors.left: startindexgetitems.right
            anchors.leftMargin: 20
            font.pixelSize: 20
        }
        Button {
            width: 130
            height: folderpathgetitems.height
            anchors.top: countgetitems.top
            anchors.left: countgetitems.right
            anchors.leftMargin: 20
            text: "Get Items"
        }
    }
}
