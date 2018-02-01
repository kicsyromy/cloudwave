import QtQuick 2.4
import Material 0.1
import QtQuick.Controls.Styles.Material 0.1

Item {
    id: root
    property alias text: button.text

    Button {
        id: button
        anchors {
            fill: parent
            topMargin: Units.dp(7)
            leftMargin: Units.dp(3)
            rightMargin: Units.dp(3)
        }

        elevation: 1
        backgroundColor: "#222222"
        textColor: "white"
    }
}
