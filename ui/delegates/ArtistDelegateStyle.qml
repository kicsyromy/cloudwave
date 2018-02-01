import QtQuick 2.4
import Material 0.1
import QtGraphicalEffects 1.0

View {
    id: background

    property url artworkSource
    property string artistName
    property bool thumbReady: false

    Image {
        id: cover
        x: Units.dp(2); y: Units.dp(2)
        width: parent.width - Units.dp(4)
        height: width - Units.dp(20)

        source: thumbReady ? artworkSource : "qrc:/ui/resources/artist_missing.png"
        fillMode: Image.PreserveAspectCrop

        onStatusChanged: {
            if (status === Image.Error) {
                cover.source = "qrc:/ui/resources/artist_missing.png"
            }
        }

        Connections {
            target: artistThumbProvider
            onThumbReady: {
                if (artistName === background.artistName) {
                    background.thumbReady = true
                }
            }
        }
    }

    DropShadow {
        id: shadow
        anchors.fill: cover
        source: cover
        color: "#80000000"
        verticalOffset: Units.dp(2)
        samples: 32
        radius: Units.dp(10.0)
        transparentBorder: true
        cached: true
    }

    Label {
        id: artistName

        anchors {
            top: cover.bottom
            topMargin: Units.dp(24)
            left: parent.left
            leftMargin: Units.dp(10)
            right: parent.right
            rightMargin: Units.dp(10)
        }

        text: background.artistName

        font {
            bold: true
            pixelSize: Units.dp(13)
        }

        color: "white"
        elide: Text.ElideRight
    }

    implicitHeight: Units.dp(36)

    radius: Units.dp(2)

    backgroundColor: backgroundColor
    elevation: 1

    Ink {
        id: mouseArea

        anchors.fill: parent

        Connections {
            target: control.__behavior
            onPressed: mouseArea.onPressed(mouse)
            onCanceled: mouseArea.onCanceled()
            onReleased: mouseArea.onReleased(mouse)
        }
    }
}
