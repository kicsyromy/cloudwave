import QtQuick 2.4
import Material 0.1

Item {
    id: root

    property color color: "white"
    
    Component {
        id: spinner
        ProgressCircle {
            color: root.color
        }
    }

    Loader {
        anchors.centerIn: parent
        sourceComponent: root.visible ? spinner : null
    }
}
