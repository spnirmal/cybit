import QtQuick
import QtQuick.Controls
import QtQuick.Window

ApplicationWindow {
    id: root
    visible: true
    visibility: Window.FullScreen
    flags: Qt.FramelessWindowHint
    title: "Cybit"

    width: 800
    height: 480
    color: "black"

    SwipeView {
        id: views
        anchors.fill: parent
        currentIndex: 1
        interactive: true

        LeftView {}
        DashboardView {}
        YTMusicView {}
    }
}
