import QtQuick 1.1
import QtWebKit 1.0

WebView {
    id: root

    function goBack() { root.back.trigger() }
    function goForward() { root.forward.trigger() }
    function pagereload() { root.reload.trigger() }
    function pagestop() { root.stop.trigger() }

    signal pageLoadStarted()
    signal pageLoadFinished(bool success)

    onLoadStarted: pageLoadStarted()
    onLoadFinished: pageLoadFinished(true)
    onLoadFailed: pageLoadFinished(false)


    width: 800
    height: 520
    preferredWidth: 800
    preferredHeight: 520

    url: "http://www.heise.de"
}
