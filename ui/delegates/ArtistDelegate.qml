import QtQuick 2.4
import QtQuick.Controls.Styles.Material 0.1
import Material 0.1

Button {
    id: root

    property url artworkSource
    property string artistName
    property bool thumbReady: false

    elevation: 1
    backgroundColor: "#222222"

    style: ButtonStyle {
        background: ArtistDelegateStyle {
            artworkSource: root.artworkSource
            artistName: root.artistName
            backgroundColor: "#222222"
            thumbReady: root.thumbReady
        }
    }
}
