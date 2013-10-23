import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    GroupBox {
        id: groupadditem
        title: "addItem(const conn::brw::BookmarkItem & a_oItem)"
        width: 750
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 30

        TextField {
            id: typeadditem
            width: 50
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 16
            maximumLength: 3
            inputMask: "999"
            text: "1"
        }
        Text {
            id: typeadditemsubtext
            text: "type"
            anchors.top: typeadditem.bottom
            anchors.left: typeadditem.left
        }
        TextField {
            id: folderpathadditem
            width: 200
            height: typeadditem.height
            anchors.top: typeadditem.top
            anchors.left: typeadditem.right
            anchors.leftMargin: 20
            font.pixelSize: 16
        }
        Text {
            text: "folder path"
            anchors.top: folderpathadditem.bottom
            anchors.left: folderpathadditem.left
        }
        TextField {
            id: titleadditem
            width: 200
            height: typeadditem.height
            anchors.top: folderpathadditem.top
            anchors.left: folderpathadditem.right
            anchors.leftMargin: 20
            font.pixelSize: 16
        }
        Text {
            text: "title"
            anchors.top: titleadditem.bottom
            anchors.left: titleadditem.left
        }
        TextField {
            id: urladditem
            width: 300
            height: typeadditem.height
            anchors.top: typeadditemsubtext.bottom
            anchors.topMargin: 10
            anchors.left: typeadditem.left
            font.pixelSize: 16
            text: "http://"
        }
        Text {
            text: "url"
            anchors.top: urladditem.bottom
            anchors.left: urladditem.left
        }
        TextField {
            id: iconpathadditem
            width: 150
            height: typeadditem.height
            anchors.top: urladditem.top
            anchors.left: urladditem.right
            anchors.leftMargin: 20
            font.pixelSize: 16
        }
        Text {
            text: "icon path"
            anchors.top: iconpathadditem.bottom
            anchors.left: iconpathadditem.left
        }
        TextField {
            id: thumbnailpathadditem
            width: 150
            height: typeadditem.height
            anchors.top: iconpathadditem.top
            anchors.left: iconpathadditem.right
            anchors.leftMargin: 20
            font.pixelSize: 16
        }
        Text {
            text: "thumbnail path"
            anchors.top: thumbnailpathadditem.bottom
            anchors.left: thumbnailpathadditem.left
        }
        Button {
            width: 130
            height: typeadditem.height
            anchors.top: titleadditem.top
            anchors.left: titleadditem.right
            anchors.leftMargin: 40
            text: "Add Item"
            onClicked: browserinterface.addBookmark(typeadditem.text, folderpathadditem.text, titleadditem.text, urladditem.text, iconpathadditem.text, thumbnailpathadditem.text)
        }
    }

    GroupBox {
        id: groupdeleteitem
        title: "deleteItem(int a_i32Uid)"
        width: 50 + 130 + 55
        anchors.top: groupadditem.bottom
        anchors.topMargin: 10
        anchors.left: groupadditem.left

        TextField {
            id: uiddeleteitem
            width: 50
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 16
            maximumLength: 3
            inputMask: "999"
            text: "1"
        }
        Text {
            text: "uid"
            anchors.top: uiddeleteitem.bottom
            anchors.left: uiddeleteitem.left
        }
        Button {
            width: 130
            height: uiddeleteitem.height
            anchors.top: uiddeleteitem.top
            anchors.left: uiddeleteitem.right
            anchors.leftMargin: 20
            text: "Delete Item"
            onClicked: browserinterface.deleteBookmark(uiddeleteitem.text)
        }
    }

    GroupBox {
        id: groupdeleteallitem
        title: "deleteAllItems(int a_i32BookmarkItemType)"
        width: 50 + 130 + 55
        anchors.top: groupdeleteitem.bottom
        anchors.topMargin: 10
        anchors.left: groupdeleteitem.left

        TextField {
            id: typedeleteall
            width: 50
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 16
            maximumLength: 3
            inputMask: "999"
            text: "1"
        }
        Text {
            text: "type"
            anchors.top: typedeleteall.bottom
            anchors.left: typedeleteall.left
        }
        Button {
            width: 130
            height: typedeleteall.height
            anchors.top: typedeleteall.top
            anchors.left: typedeleteall.right
            anchors.leftMargin: 20
            text: "Delete All Items"
            onClicked: browserinterface.deleteAllBookmarks(typedeleteall.text)
        }
    }


    GroupBox {
        id: groupgetitems
        title: "getItems(&a_strParentFolderPath, a_i32BookmarkType, a_eSortingOrder, a_u32StartIndex, a_u32ItemsCount, &a_oItems)"
        width: 660
        anchors.top: groupdeleteallitem.bottom
        anchors.topMargin: 10
        anchors.left: groupdeleteallitem.left

        TextField {
            id: folderpathgetitems
            width: 150
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 16
        }
        Text {
            text: "folder path"
            anchors.top: folderpathgetitems.bottom
            anchors.left: folderpathgetitems.left
        }
        TextField {
            id: typegetitems
            width: 50
            height: folderpathgetitems.height
            anchors.top: folderpathgetitems.top
            anchors.left: folderpathgetitems.right
            anchors.leftMargin: 20
            font.pixelSize: 16
            maximumLength: 3
            inputMask: "999"
            text: "1"
        }
        Text {
            text: "type"
            anchors.top: typegetitems.bottom
            anchors.left: typegetitems.left
        }
        ComboBox {
            id: sortinggetitems
            width: 100
            model: ["unsorted", "title ascending", "title descending", "url acending", "url descending"]
            height: folderpathgetitems.height
            anchors.top: typegetitems.top
            anchors.left: typegetitems.right
            anchors.leftMargin: 20
        }
        Text {
            text: "sorting"
            anchors.top: sortinggetitems.bottom
            anchors.left: sortinggetitems.left
        }
        SpinBox {
            id: startindexgetitems
            width: 50
            height: folderpathgetitems.height
            anchors.top: sortinggetitems.top
            anchors.left: sortinggetitems.right
            anchors.leftMargin: 20
            font.pixelSize: 16
        }
        Text {
            text: "start index"
            anchors.top: startindexgetitems.bottom
            anchors.left: startindexgetitems.left
        }
        SpinBox {
            id: countgetitems
            width: 50
            height: folderpathgetitems.height
            anchors.top: startindexgetitems.top
            anchors.left: startindexgetitems.right
            anchors.leftMargin: 20
            font.pixelSize: 16
            value: 1
        }
        Text {
            text: "count"
            anchors.top: countgetitems.bottom
            anchors.left: countgetitems.left
        }
        Button {
            width: 130
            height: folderpathgetitems.height
            anchors.top: countgetitems.top
            anchors.left: countgetitems.right
            anchors.leftMargin: 20
            text: "Get Items"
            onClicked: browserinterface.getBookmarks(folderpathgetitems.text, typegetitems.text, sortinggetitems.currentIndex, startindexgetitems.value, countgetitems.value)
        }
    }
}
