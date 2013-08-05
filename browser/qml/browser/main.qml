import QtQuick 2.0
import QtWebKit 3.0

WebView {
    id: root

    signal pageLoadStarted(string url)
    signal pageLoadFinished(bool success)

    onLoadingChanged: {
        if(loadRequest.status === WebView.LoadStartedStatus)
            pageLoadStarted(loadRequest.url)
        else if(loadRequest.status === WebView.LoadSucceededStatus)
            pageLoadFinished(true)
        else if(loadRequest.status === WebView.LoadFailedStatus)
            pageLoadFinished(false)
    }

    width: 800
    height: 520

    url: "http://www.genivi.org"
}
