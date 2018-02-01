import QtQuick 2.4
import Material 0.1

Item{
    id: root

    property Flickable flickable
    property bool refreshing: false
    property int offset: Units.dp(180)
    property alias pullText: pullLabel.text
    property alias releaseText: releaseLabel.text
    property alias refreshText: refreshLabel.text
    property bool available: false

    width: flickable.width

    Binding {
        target: root
        property: "height"
        value: -flickable.contentY
        when: !root.refreshing
    }

    // Main magic is here
    onHeightChanged: {
        if (height > Units.dp(40) && height > offset)
            timer.start()
    }

    visible: available && (refreshing || height > (offset / 2))

    signal requestRefresh

    Row {
        id: container
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: Units.dp(5)

        Image {
            id: refreshIcon

            y: Units.dp(-4)
            width: 32
            height: 32

            visible: !refreshing

            source: "qrc:/ui/resources/refresh.png"
            rotation: 4 * container.y
        }

        Label {
            id: pullLabel

            font.pixelSize: Units.dp(20)
            color: "white"
            text: "Pull to refresh..."
            visible: !refreshing && root.height < offset
        }

        Label {
            id: releaseLabel

            font.pixelSize: Units.dp(20)
            color: "white"
            text: "Release to refresh..."
            visible: !refreshing && root.height >= offset
        }

        Label {
            id: refreshLabel
            y: Units.dp(30)

            font.pixelSize: Units.dp(20)
            color: "white"
            visible: refreshing
        }
    }

    Timer {
        id: timer
        interval: 300
        running: false
        repeat: false
        onTriggered: {
            if (flickable.contentY > -(offset / 10)) {
                refreshing = true
                root.requestRefresh()
            }
        }
    }
}

