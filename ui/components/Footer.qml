import QtQuick 2.4
import Material 0.1
import QtGraphicalEffects 1.0

import Playback 1.0

Item {
    id: root

    anchors.bottom: parent.bottom
    z: 100

    signal clicked

    function show() {
        console.log("Show called for footer");
        root.state = ""
    }

    function hide() {
        root.state = "hidden"
    }

    states: State {
        name: "hidden"
        PropertyChanges {
            target: root
            anchors.bottomMargin: -(root.height + 1)
        }
    }

    transitions: Transition {
        NumberAnimation {
            properties: "anchors.bottomMargin"
            duration: MaterialAnimation.pageTransitionDuration
            easing.type: Easing.InOutQuad
        }
    }

    Rectangle {
        id: footer
        anchors.fill: parent
        color: "#202020"

        MouseArea {
            anchors.fill: parent
            onClicked: root.clicked()
        }
    }

    DropShadow {
        id: backgroundShadow
        anchors.fill: footer
        source: footer
        color: "#80000000"
        verticalOffset: Units.dp(-1)
        samples: 32
        radius: Units.dp(10.0)
        transparentBorder: true
        cached: true
    }

    Row {
        id: iconContainer
        spacing: Units.dp(12)
        width: childrenRect.width
        height: childrenRect.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Units.dp(10)

        Image {
            id: prevButton
            y: Units.dp(3)
            width: Units.dp(30)
            height: width
            source: "qrc:/ui/resources/previous.png"
            MouseArea {
                anchors.fill: parent
                onClicked: playlist.previous()
            }
        }

        Image {
            id: playPauseButton
            width: Units.dp(35)
            height: width
            source: playlist.playing ? "qrc:/ui/resources/pause.png" : "qrc:/ui/resources/play_arrow.png"
            MouseArea {
                anchors.fill: parent
                onClicked: playlist.playing ? playlist.pause() : playlist.play()
            }
        }

        Image {
            id: nextButton
            y: Units.dp(3)
            width: Units.dp(30)
            height: width
            source: "qrc:/ui/resources/next.png"
            MouseArea {
                anchors.fill: parent
                onClicked: playlist.next()
            }
        }
    }

    Scope {
        id: scope
        anchors {
            right: parent.right
            rightMargin: Units.dp(10)
            verticalCenter: parent.verticalCenter
        }
    }

    Label {
        id: infoLabel
        anchors {
            left: iconContainer.right
            leftMargin: Units.dp(10)
            right: scope.left
            rightMargin: Units.dp(10)
            verticalCenter: parent.verticalCenter
        }

        text: playlist.nowPlaying.song() + " by " + playlist.nowPlaying.artist()
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        font.pixelSize: Units.dp(16)
        color: "white"
    }
}
