import QtQuick 2.0
import Material 0.1

Item {
    id: root

    property alias delegate: view.delegate
    property alias model: view.model
    property alias header: view.header
    property alias count: view.count
    property alias view: view
    property alias pullToRefreshAvailable: pullToRefresh.available
    property int bottomMargin: Units.dp(64)

    readonly property bool loading: view.count < 1

    signal requestRefresh

    ListView {
        id: view
        anchors.fill: parent
        anchors.bottomMargin: root.bottomMargin
        onCountChanged: {
            if (count > 0) pullToRefresh.refreshing = false
        }
    }

    PullToRefresh {
        id: pullToRefresh
        anchors.top: view.top
        flickable: view
        onRequestRefresh: root.requestRefresh()
    }

    Scrollbar {
        flickableItem: view

        Component.onCompleted: {
            children[0].color = "white"
        }
    }
}
