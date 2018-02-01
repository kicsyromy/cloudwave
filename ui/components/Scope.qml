import QtQuick 2.4
import Material 0.1

AnimatedImage {
    source: "qrc:/ui/resources/scope.gif"
    width: Units.dp(40)
    height: Units.dp(28)
    playing: playlist.playing
    fillMode: Image.PreserveAspectCrop
}
