import QtQuick 2.0
import QtQuick.Controls 1.2
import Material 0.1

Item {
    id: root

    property alias delegate: view.delegate
    property alias model: view.model
    property alias count: view.count
    property alias cellWidth: view.cellWidth
    property alias cellHeight: view.cellHeight
    property int bottomMargin: Units.dp(62)
    property alias pullToRefreshAvailable: pullToRefresh.available

    readonly property bool loading: view.count < 1

    signal requestRefresh

    GridView {
        id: view
        width: Math.floor(parent.width / cellWidth) * cellWidth
        height: parent.height - root.bottomMargin
        anchors.horizontalCenter: parent.horizontalCenter
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

        anchors {
            right: root.right
        }

        Component.onCompleted: {
            children[0].color = "white"
        }
    }
}
