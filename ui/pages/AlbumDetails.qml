import QtQuick 2.4
import Material 0.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles.Material 0.1
import "../components" as Components
import "../delegates"

Page {
    id: page

    property var album

    QtObject {
        id: priv
        property string title
        property string artist
        property string genre
        property int songCount
        property url artwork
    }

    Component {
        id: albumDetails
        Item {
            width: page.width
            height: Units.dp(300)

            Item {
                id: coverImage
                width: parent.width
                height: Units.dp(200)

                Image {
                    id: cover
                    x: Units.dp(50); y: Units.dp(20)
                    width: height
                    height: parent.height - Units.dp(4)

                    source: priv.artwork

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

                Column {
                    y: cover.y

                    anchors {
                        left: cover.right
                        leftMargin: Units.dp(15)
                        verticalCenter: parent.verticalCenter
                    }

                    spacing: Units.dp(10)

                    Label {
                        color: "white"
                        text: priv.title
                        font.pixelSize: Units.dp(17)
                        font.bold: true
                    }

                    Label {
                        color: "white"
                        text: priv.artist
                        font.pixelSize: Units.dp(17)
                        font.bold: false
                    }

                    Label {
                        color: "white"
                        text: priv.genre
                        font.pixelSize: Units.dp(17)
                        font.bold: false
                    }

                    Label {
                        color: "white"
                        text: priv.songCount + " song(s)"
                        font.pixelSize: Units.dp(17)
                        font.bold: false
                    }
                }
            }


            Row {
                anchors.top: coverImage.bottom
                anchors.topMargin: Units.dp(35)
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Units.dp(20)
                Components.ButtonWithIcon {
                    id: playButton
                    width: Units.dp(100)
                    height: Units.dp(50)
                    iconSource: "qrc:/ui/resources/play_arrow.png"
                    iconSize: Qt.size(Units.dp(22), Units.dp(22))
                    text: "play"
                    onClicked: {
                        playlist.play(albumDetailsModel.tracks())
                    }
                }

                Components.ButtonWithIcon {
                    id: shuffleButton
                    width: Units.dp(150)
                    height: Units.dp(50)
                    iconSource: "qrc:/ui/resources/shuffle.png"
                    iconSize: Qt.size(Units.dp(22), Units.dp(22))
                    text: "shuffle"
                    onClicked: {
                        playlist.play(albumDetailsModel.tracks(), true)
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
        model: albumDetailsModel
        header: view.count > 0 ? albumDetails : null
        delegate: TrackDelegate {
            width: view.width
            height: Units.dp(70)
            text: songTitle + " by " + songArtist
            albumArt: priv.artwork
            onClicked: {
                playlist.appendAndPlay(track)
            }
        }

        onCountChanged: {
            if (count > 0)
                view.view.positionViewAtBeginning()
        }
    }

    Component.onCompleted: {
        albumDetailsModel.loadDetails(album)
        priv.title = albumDetailsModel.albumTitle()
        priv.artist = albumDetailsModel.artistName()
        priv.genre = albumDetailsModel.genre()
        priv.songCount = albumDetailsModel.songCount()
        priv.artwork = "image://albumthumbnails/" + priv.title
    }
}
