import QtQuick 2.4
import Material 0.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles.Material 0.1
import "../components" as Components

ButtonStyle {
    id: root

    property url albumArt
    property bool isPlaying: false

    signal clicked

    background: View {
        id: background

        Image {
            id: cover
            x: Units.dp(2); y: Units.dp(2)
            width: height
            height: parent.height - Units.dp(4)

            source: root.albumArt

            onStatusChanged: {
                if (status === Image.Error) {
                    cover.source = "qrc:/ui/resources/album_missing.png"
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

        Component {
            id: scope
            Components.Scope { }
        }

        Loader {
            id: scopeLoader

            anchors {
                right: parent.right
                rightMargin: Units.dp(10)
                verticalCenter: parent.verticalCenter
            }

            sourceComponent: root.isPlaying ? scope : null
        }

        Label {
            anchors.left: cover.right
            anchors.leftMargin: Units.dp(10)
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width

            font.pixelSize: Units.dp(15)
            color: "white"
            elide: Text.ElideRight
            text: control.text
        }

        implicitHeight: Units.dp(36)

        radius: Units.dp(2)

        backgroundColor: "#222222"
        elevation: 1

        Ink {
            id: mouseArea

            anchors.fill: parent

            Connections {
                target: control.__behavior
                onPressed: mouseArea.onPressed(mouse)
                onCanceled: mouseArea.onCanceled()
                onReleased: mouseArea.onReleased(mouse)
                onClicked: root.clicked()
            }
        }
    }

    label: Item {}
}
