import QtQuick 1.1
import QtWebKit 1.0

Flickable {
    id: root

    property alias url: webcontent.url
    property alias progress: webcontent.progress
    property alias title: webcontent.title
    property alias contentheight: webcontent.height
    property alias contentwidth: webcontent.width

    function goBack() { webcontent.back.trigger() }
    function goForward() { webcontent.forward.trigger() }
    function pagereload() { webcontent.reload.trigger() }
    function pagestop() { webcontent.stop.trigger() }

    signal pageLoadStarted()
    signal pageLoadFinished(bool success)

    width: 800
    height: 520

    contentWidth: Math.max(root.width,webcontent.width)
    contentHeight: Math.max(root.height,webcontent.height)

    WebView {
        id: webcontent

        onLoadStarted: root.pageLoadStarted()
        onLoadFinished: {
            console.log(root.height, webcontent.height)
            root.pageLoadFinished(true)
        }
        onLoadFailed: root.pageLoadFinished(false)

        preferredWidth: root.width
        preferredHeight: root.height

        url: "http://www.heise.de"
    }
}
