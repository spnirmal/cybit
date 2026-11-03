import QtQuick

Item {
    id: root

    property int imageIndex: 0

    Image {
        anchors.fill: parent
        source: backgroundImages.length > 0
                ? backgroundImages[root.imageIndex]
                : ""
        fillMode: Image.PreserveAspectCrop
        asynchronous: true
    }

    Timer {
        interval: 150000
        running: backgroundImages.length > 1
        repeat: true

        onTriggered: {
            root.imageIndex =
                (root.imageIndex + 1) % backgroundImages.length
        }
    }
}
