import QtQuick 2.4
import Material 0.1
import "pages" as Pages
import "components" as Components

import Constants 1.0 as Constants

ApplicationWindow {
    id: mainWindow
    title: qsTr("SonicWave")
    width: 720
    height: 1280

    visible: true

    initialPage: mainPage

    QtObject {
        id: selections
        property var selectedAlbum
        property var selectedArtist
        property var selectedGenre
        property bool playlistShown: false
    }

    theme {
        accentColor: "white"
        primaryColor: "#202020"
        primaryDarkColor: "#111111"
        backgroundColor: "#111111"
    }

    Component {
        id: mainPage
        Pages.MainPage {
            onRequestPage: {
                switch (pageId)
                {
                case Constants.Page.AlbumDetails:
                    selections.selectedAlbum = data
                    mainWindow.pageStack.push(albumDetails)
                    break;
                case Constants.Page.ArtistDetails:
                    selections.selectedArtist = data
                    mainWindow.pageStack.push(artistDetails)
                    break;
                case Constants.Page.GenreDetails:
                    selections.selectedGenre = data
                    break;
                }
            }
        }
    }

    Component {
        id: albumDetails
        Pages.AlbumDetails {
            album: selections.selectedAlbum
        }
    }

    Component {
        id: artistDetails
        Pages.ArtistDetails {
            artist: selections.selectedArtist
            onAlbumClicked: {
                selections.selectedAlbum = album
                mainWindow.pageStack.push(albumDetails)
            }
        }
    }

    Component {
        id: playlistPage
        Pages.Playlist {
        }
    }

    Connections {
        target: playlist
        onNowPlayingChanged: {
            if (!selections.playlistShown) footer.show()
        }
    }

    Components.Footer {
        id: footer
        width: mainWindow.width
        height: Units.dp(60)

        onClicked: {
            mainWindow.pageStack.push(playlistPage)
            var plPage = mainWindow.pageStack.currentItem
            plPage.backAction.triggered.connect(footer.show)
            footer.hide()
            selections.playlistShown = true
        }

        Component.onCompleted: {
            footer.hide()
        }
    }
}
