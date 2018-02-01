import QtQuick 2.0
import Material 0.1
import "../components" as Components
import "../delegates"

Item {
    id: root

    property bool inView: false

    property bool __loading: true

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
//    Components.Spinner {
//        id: spinner
//        anchors.centerIn: parent
//        visible: root.__loading || viewLoader.status == Loader.Loading
//    }

    Component {
        id: viewSource

        Components.ListView {
            id: view
            pullToRefreshAvailable: true

            onRequestRefresh: genreListModel.refresh()

            model: genreListModel
            delegate: GenreDelegate {
                width: view.width
                height: Units.dp(70)
                text: name
            }

            Binding {
                target: root
                property: "__loading"
                value: view.loading
            }
        }
    }

    Loader {
        id: viewLoader
        anchors.fill: parent
    }
}
