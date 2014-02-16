import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: root
    anchors.fill: parent

    GroupBox {
        id: group_box2
        y: 0
        width: 9
        title: "Fetch cache properties"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        GroupBox { id: cacheSizeGroup;
        width: -16
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Text {
                id: textCacheSize
                y: 0
                text: qsTr("")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.verticalCenter: cacheSizeButton.verticalCenter
                font.pixelSize: 12
            }

            Button {
                id: cacheSizeButton
                x: 156
                width: maxCacheSizeButton.width
                text: "Get cache size"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                onClicked: textCacheSize.text = cachemanagerinterface.getCacheSize()
            }

            Button {
                id: maxCacheSizeButton
                x: -129
                y: 47
                width: 158
                height: 31
                text: "Get max cache size"
                anchors.horizontalCenter: cacheSizeButton.horizontalCenter
                anchors.topMargin: 10
                anchors.top: cacheSizeButton.bottom
                onClicked: textMaxCacheSize.text = cachemanagerinterface.getMaximumCacheSize()
            }

            Text {
                id: textMaxCacheSize
                y: 48
                text: qsTr("")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.verticalCenterOffset: 0
                font.pixelSize: 12
                anchors.verticalCenter: maxCacheSizeButton.verticalCenter
            }

            Button {
                id: getCachePolicyButton
                x: -422
                width: maxCacheSizeButton.width
                text: "Get cache policy"
                anchors.top: maxCacheSizeButton.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: cacheSizeButton.horizontalCenter
        onClicked:textCachePolicy.text = cachemanagerinterface.getCachePolicy();
            }

            Text {
                id: textCachePolicy
                y: 79
                text: qsTr("")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.verticalCenter: getCachePolicyButton.verticalCenter
                font.pixelSize: 12
            }

            Button {
                id: clearCacheButton
                x: -376
                width: getCachePolicyButton.width
                text: "Clear cache"
                anchors.top: getCachePolicyButton.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: cacheSizeButton.horizontalCenter
        onClicked: cachemanagerinterface.clearCache();
}

}
    }

    GroupBox {
    id: group_box1
    height: setCachePolicyGroup.height
    anchors.top: group_box2.bottom
    anchors.topMargin: 20
    anchors.right: parent.right
    anchors.rightMargin: 0
    anchors.left: parent.left
    anchors.leftMargin: 0
    title: "Cache Settings"

    GroupBox {
        id: setCachePolicyGroup
        x: 185
        y: 0
        height: onlineCacheButton.height
        title: ""
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            id: onlineOnlyButton
            x: 127
            y: 6
            width: onlineCacheButton.width
            text: "CP_ONLINE_ONLY"
            anchors.left: cacheOnlyButton.right
            anchors.leftMargin: 0
            anchors.verticalCenter: onlineCacheButton.verticalCenter
        onClicked: cachemanagerinterface.setCachePolicy(2);
        }

        Button {
            id: cacheOnlyButton
            x: 42
            y: 6
            width: onlineCacheButton.width
            text: "CP_CACHE_ONLY"
            anchors.left: onlineCacheButton.right
            anchors.leftMargin: 0
            anchors.verticalCenter: onlineCacheButton.verticalCenter
        onClicked: cachemanagerinterface.setCachePolicy(1);
        }

        Button {
            id: onlineCacheButton
            width: 170
            height: 31
            text: "CP_ONLINE_CACHE"
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        onClicked: cachemanagerinterface.setCachePolicy(0);
        }



}
}




}


