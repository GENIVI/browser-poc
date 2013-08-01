import QtQuick 2.0
import QtWebKit 3.0

WebView {
    id: root

    signal urlChanged(int status, string url)

    onLoadingChanged: urlChanged(loadRequest.status, loadRequest.url)

    width: 800
    height: 520

    url: "http://www.genivi.org"
}
