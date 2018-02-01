import QtQuick 2.0
import Material 0.1
import "../components"
import "../delegates"

Item {
    id: root

    property bool inView: false

    property bool __loading: true

    signal itemClicked(var item)

    onInViewChanged: {
        if (root.inView) viewLoader.sourceComponent = viewSource
    }

    Timer {
        running: root.inView == false
        onTriggered: {
            viewLoader.sourceComponent = null
        }
    }

// No spinners, they eat up CPU like hot cake
//    Spinner {
//        id: spinner
//        anchors.centerIn: parent
//        visible: (root.__loading || viewLoader.status == Loader.Loading) && !albumListModel.searching
//    }

    Component {
        id: viewSource
        FlowView {
            id: view
            cellWidth: Units.dp(175)
            cellHeight: Units.dp(245)
            pullToRefreshAvailable: true

            onRequestRefresh: albumListModel.refresh()

            Binding {
                target: root
                property: "__loading"
                value: view.loading
            }

            model: albumListModel
            delegate: Item {
                width: view.cellWidth
                height: view.cellHeight

                AlbumDelegate {
                    id: delegate
                    width: Units.dp(170)
                    height: Units.dp(240)

                    anchors.centerIn: parent

                    albumTitle: title
                    artistName: artist
                    coverSource: "image://albumThumbnails/" + title
                    onClicked: root.itemClicked(album)

                    Component.onCompleted: {
                        delegate.thumbReady = albumThumbProvider.prepareThumb(album)
                    }
                }
            }
        }
    }

    Loader {
        id: viewLoader
        anchors {
            fill: parent
            topMargin: Units.dp(8)
        }
    }
}
