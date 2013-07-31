import QtQuick 2.0
import QtWebKit 3.0

WebView {
    id: root

//    onLoadingChanged: console.log("OOOOOOOOOOO " + loadRequest.status + " " + loadRequest.url)
//    onLinkHovered:console.log("IIIIIIIIII" + hoveredUrl)

    width: 800
    height: 520

    url: "http://www.genivi.org"
}
