import QtQuick 2.4
import Material 0.1
import QtQuick.Controls.Styles.Material 0.1

Button {
    id: root

    elevation: 1
    backgroundColor: "#202020"

    property size iconSize

    style: ButtonStyle {
        label: Item {
            Row {
                anchors.centerIn: parent
                spacing: Units.dp(15)

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: root.iconSource
                    width: iconSize.width
                    height: iconSize.height
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    text: root.text
                    style: "button"
                    color: "white"
                }
            }
        }
    }
}
