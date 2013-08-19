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

    signal onInputText(string a_strInputName, string a_strDefaultInputValue, string a_i32InputValueType, int a_s32MaxLength, int a_s32Max, int a_s32Min, int a_s32Step)

    width: 800
    height: 520

    contentWidth: Math.max(root.width,webcontent.width)
    contentHeight: Math.max(root.height,webcontent.height)

    WebView {
        id: webcontent

        onLoadStarted: root.pageLoadStarted()
        onLoadFinished: {
//            console.log(root.height, webcontent.height)
            root.pageLoadFinished(true)
//            webcontent.evaluateJavaScript("var inputs = document.getElementsByTagName('INPUT');var index;for(index=0; index < inputs.length; index++){inputs[index].onfocus = function() {window.webpage.getFocus(index, inputs.length, inputs[index].name,inputs[index].value,inputs[index].type,inputs[index].maxlength,inputs[index].max,inputs[index].min,inputs[index].step)};inputs[index].onblur = function(){window.webpage.leaveFocus()}}")
            webcontent.evaluateJavaScript("var inputs = document.getElementsByTagName('INPUT');var index;for(index=0; index < inputs.length; index++){ inputs[index].onfocus = function() {window.webpage.getFocus(this.name, this.value, this.type, this.maxlength, this.max, this.min, this.step) }}")



//            webcontent.evaluateJavaScript("var inputs = document.getElementsByTagName('INPUT'); var element = inputs[2]; element.value='Hello'")
        }
        onLoadFailed: root.pageLoadFinished(false)

        preferredWidth: root.width
        preferredHeight: root.height

        focus: true

        url: "http://www.bmw.com"

//        settings.javaEnabled: true
        settings.developerExtrasEnabled: true
        javaScriptWindowObjects: QtObject {
            WebView.windowObjectName: "webpage"

            function getFocus(name, value, type, maxlength, max, min, step) {
//                console.log("Input has focus " + name + " " + value
//                            + " " + type + " " + maxlength + " " + max
//                            + " " + min + " " + step);
                onInputText(name, value, type, maxlength, max, min, step);
            }
            function leaveFocus() { console.log("Input lost focus"); }
        }
    }
}
