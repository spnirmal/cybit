import QtQuick
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow {
    id: root
    visible: true
    visibility: Window.FullScreen
    flags: Qt.FramelessWindowHint
    title: "Cybit"

    width: Screen.width
    height: Screen.height
    color: "black"

    Image {
        id: bgImage
        anchors.fill: parent
        source: "qrc:/qt/qml/Cybit/assets/image.png"
        fillMode: Image.PreserveAspectRatio
        smooth: true
        mipmap: true
    }

    Component.onCompleted: {
        console.log("Window Geometry:", width, "x", height)
        console.log("Screen Geometry:", Screen.width, "x", Screen.height)
    }
}
