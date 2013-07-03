import QtQuick 2.0
import QtWebKit 3.0

Rectangle {
    width: 800
    height: 600
    color: "blue"

    WebView {
        anchors.fill: parent
        url: "http://www.genivi.org"
    }
}
