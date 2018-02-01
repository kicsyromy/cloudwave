import QtQuick 2.4
import Material 0.1

Item {
    id: root

    property alias text: button.text
    property url albumArt
    property bool isPlaying: false

    signal clicked

    Button {
        id: button
        anchors {
            fill: parent
            topMargin: Units.dp(7)
            leftMargin: Units.dp(3)
            rightMargin: Units.dp(3)
        }

        style: TrackDelegateStyle {
            isPlaying: root.isPlaying
            albumArt: root.albumArt
            onClicked: root.clicked()
        }
    }
}
