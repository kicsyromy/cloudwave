import QtQuick 2.4
import Material 0.1
import QtQuick.Controls.Styles.Material 0.1
import "../components" as Components
import "../delegates"

import Playback 1.0

Page {
    id: page

    actions: [
        Action {
            iconName: "av/shuffle"
            name: "Shuffle"
        },

        Action {
            iconName: "av/repeat"
            name: "Repeat"
        }
    ]

    Image {
        id: background
        anchors.fill: parent
        source: "image://albumThumbnails/" + playlist.nowPlaying.album()
        fillMode: Image.PreserveAspectCrop
        opacity: 0.03
    }

    Components.ListView {
        id: view

        anchors {
            top: controls.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        bottomMargin: Units.dp(3)

        model: playListModel
        delegate: TrackDelegate {
            width: view.width
            height: Units.dp(70)
            text: title + " by " + artist
            albumArt: "image://albumThumbnails/" + album
            isPlaying: title === playlist.nowPlaying.song() && artist === playlist.nowPlaying.artist()
            onClicked: {
                playlist.play(index)
            }
        }

        clip: true
    }

    Item {
        id: controls
        height: parent.height / 3

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        Image {
            id: cover

            anchors {
                top: parent.top
                topMargin: Units.dp(20)
                bottom: parent.bottom
                bottomMargin: Units.dp(15)
                left: parent.left
                leftMargin: Units.dp(20)
            }

            width: height

            source: "image://albumThumbnails/" + playlist.nowPlaying.album()
        }

        Item {
            id: details

            anchors {
                left: cover.right
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            Item {
                id: controlContainer
                width: childrenRect.width
                height: childrenRect.height

                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                    bottomMargin: Units.dp(30)
                }

                Row {
                    spacing: Units.dp(35)
                    width: childrenRect.width
                    height: childrenRect.height

                    Image {
                        id: prevButton
                        y: Units.dp(14)
                        width: Units.dp(60)
                        height: width
                        source: "qrc:/ui/resources/previous.png"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: playlist.previous()
                        }
                    }

                    Image {
                        id: playPauseButton
                        width: Units.dp(80)
                        height: width
                        source: playlist.playing ? "qrc:/ui/resources/pause.png" : "qrc:/ui/resources/play_arrow.png"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: playlist.playing ? playlist.pause() : playlist.play()
                        }
                    }

                    Image {
                        id: nextButton
                        y: Units.dp(14)
                        width: Units.dp(60)
                        height: width
                        source: "qrc:/ui/resources/next.png"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: playlist.next()
                        }
                    }
                }
            }

            Item {
                id: sliderContainer
                width: parent.width
                height: childrenRect.height
                anchors {
                    bottom: parent.bottom
                    bottomMargin: Units.dp(10)
                }

                function parseTime(milliseconds) {
                    var min = (milliseconds / 1000 / 60) << 0
                    var sec = Math.ceil((milliseconds / 1000) % 60)

                    if (sec === 60) {
                        sec = 0;
                        min++
                    }

                    var minStr = min < 10 ? "0" + min : min
                    var secStr = sec < 10 ? "0" + sec : sec

                    return minStr + ":" + secStr
                }

                Label {
                    id: currentTime

                    anchors.left: parent.left
                    anchors.leftMargin: Units.dp(20)

                    text: sliderContainer.parseTime(slider.value)
                    style: "button"
                    color: "white"
                }

                Slider {
                    id: slider

                    anchors {
                        left: currentTime.right
                        leftMargin: Units.dp(20)
                        right: totalTime.left
                        rightMargin: Units.dp(20)
                    }

                    maximumValue: playlist.nowPlaying.duration
                    color: "white"

                    onPressedChanged: {
                        if (!slider.pressed)
                            playlist.nowPlaying.seek(slider.value)
                    }

                    Connections {
                        target: playlist.nowPlaying
                        onPositionChanged: {
                            if (!slider.pressed)
                                slider.value = playlist.nowPlaying.position
                        }
                    }
                }

                Label {
                    id: totalTime

                    anchors.right: parent.right
                    anchors.rightMargin: Units.dp(20)

                    text: sliderContainer.parseTime(playlist.nowPlaying.duration)
                    style: "button"
                    color: "white"
                }
            }
        }
    }
}
