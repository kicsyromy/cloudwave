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
//        visible: (root.__loading || viewLoader.status == Loader.Loading) && !artistListModel.searching
//    }

    Component {
        id: viewSource
        FlowView {
            id: view
            cellWidth: Units.dp(175)
            cellHeight: Units.dp(225)
            pullToRefreshAvailable: true

            onRequestRefresh: artistListModel.refresh()

            Binding {
                target: root
                property: "__loading"
                value: view.loading
            }

            model: artistListModel
            delegate: Item {
                width: view.cellWidth
                height: view.cellHeight

                ArtistDelegate {
                    id: delegate
                    width: Units.dp(170)
                    height: Units.dp(220)

                    anchors.centerIn: parent

                    artistName: name
                    artworkSource: "image://artistThumbnails/" + name
                    onClicked: root.itemClicked(artist)

                    Component.onCompleted: {
                        delegate.thumbReady = artistThumbProvider.prepareThumb(artist)
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
