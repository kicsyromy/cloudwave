import QtQuick 2.4
import Material 0.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles.Material 0.1
import "../components" as Components
import "../delegates"

Page {
    id: page

    property var artist

    signal albumClicked(var album)

    QtObject {
        id: priv
        property string name
        property string summary
        property url thumbnail
    }

    Component {
        id: artistDetails
        Item {
            width: page.width
            height: Units.dp(250)

            Item {
                id: coverImage
                width: parent.width
                height: Units.dp(200)

                Image {
                    id: cover
                    x: Units.dp(50); y: Units.dp(20)
                    width: height
                    height: parent.height - Units.dp(4)
                    fillMode: Image.PreserveAspectCrop

                    source: priv.thumbnail

                    onStatusChanged: {
                        if (status === Image.Error) {
                            cover.source = "qrc:/ui/resources/artist_missing.png"
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

                Column {
                    y: cover.y

                    anchors {
                        left: cover.right
                        leftMargin: Units.dp(15)
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    spacing: Units.dp(10)

                    Label {
                        color: "white"
                        text: priv.name
                        font.pixelSize: Units.dp(17)
                        font.bold: true
                    }

                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.rightMargin: Units.dp(20)
                        color: "white"
                        text: priv.summary
                        font.pixelSize: Units.dp(17)
                        font.bold: false
                        maximumLineCount: 5
                        wrapMode: Text.WordWrap
                        elide: Text.ElideRight
                    }
                }
            }
        }
    }

    Components.ListView {
        id: view

        Components.Spinner {
            anchors.centerIn: parent
            visible: view.count < 1
        }

        anchors.fill: parent
        model: artistDetailsModel
        header: view.count > 0 ? artistDetails : null
        delegate: TrackDelegate {
            width: view.width
            height: Units.dp(70)
            text: title
            albumArt: "image://albumThumbnails/" + title
            onClicked: {
                page.albumClicked(album)
            }
        }

        onCountChanged: {
            if (count > 0)
                view.view.positionViewAtBeginning()
        }
    }

    Component.onCompleted: {
        artistDetailsModel.loadDetails(page.artist)
        priv.name = artistDetailsModel.artistName()
        priv.summary = artistDetailsModel.summary()
        priv.thumbnail = "image://artistThumbnails/" + priv.name
    }
}
