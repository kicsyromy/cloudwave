import QtQuick 2.4
import QtQuick.Controls.Styles.Material 0.1
import Material 0.1

Button {
    id: root

    property url coverSource
    property string albumTitle
    property string artistName
    property bool thumbReady: false

    elevation: 1
    backgroundColor: "#222222"

    style: ButtonStyle {
        background: AlbumDelegateStyle {
            coverSource: root.coverSource
            albumTitle: root.albumTitle
            artistName: root.artistName
            thumbReady: root.thumbReady
            backgroundColor: "#222222"
        }
    }
}
