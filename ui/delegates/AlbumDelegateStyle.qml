import QtQuick 2.4
import Material 0.1
import QtGraphicalEffects 1.0

View {
    id: background

    property url coverSource
    property string albumTitle
    property string artistName
    property bool thumbReady

    Image {
        id: cover
        x: Units.dp(2); y: Units.dp(2)
        width: parent.width - Units.dp(4)
        height: width

        source: thumbReady ? coverSource : "qrc:/ui/resources/album_missing.png"

        onStatusChanged: {
            if (status === Image.Error) {
                cover.source = "qrc:/ui/resources/album_missing.png"
            }
        }

        Connections {
            target: albumThumbProvider
            onThumbReady: {
                if (albumTitle === background.albumTitle) {
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
        id: albumTitle

        anchors {
            top: cover.bottom
            topMargin: Units.dp(16)
            left: parent.left
            leftMargin: Units.dp(10)
            right: parent.right
            rightMargin: Units.dp(10)
        }

        text: background.albumTitle

        font {
            bold: true
            pixelSize: Units.dp(13)
        }

        color: "white"
        elide: Text.ElideRight
    }

    Label {
        id: artistName

        anchors {
            top: albumTitle.bottom
            topMargin: Units.dp(10)
            left: parent.left
            leftMargin: Units.dp(10)
            right: parent.right
            rightMargin: Units.dp(10)
        }

        text: background.artistName

        font.pixelSize: Units.dp(11)

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
