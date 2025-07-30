import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Window {
    objectName: "TitleBarWindow"
    id: titleBarWindow
    width: Screen.width
    height: 90
    visible: true
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    Rectangle {
        id: topBarBg
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50
        color: "grey"

        RowLayout {
            anchors.fill: parent
            anchors.margins: 10

            Item {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter

                Row {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 8

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: "\uf0ac"                     // globe icon
                        font.family: faSolidFontFamily
                        font.pixelSize: 22
                        color: "white"
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        id: coordLabel
                        text: "5043.599'N 00032.461'W"
                        color: "white"
                        font.pixelSize: 22
                    }
                }
            }

            Item {
                id: clockItem
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter

                property string currentTime: Qt.formatTime(new Date(), "h:mm ap")

                Timer {
                    interval: 1000
                    running: true
                    repeat: true
                    onTriggered: {
                        // explicitly write back into the Item’s property
                        clockItem.currentTime = Qt.formatTime(new Date(), "h:mm ap")
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: clockItem.currentTime
                    color: "white"
                    font.pixelSize: 22
                }
            }


            Item {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter

                Row {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10

                    Label {
                        text: "\uf293"
                        font.family: faSolidFontFamily
                        font.pixelSize: 20
                        color: "white"
                    }
                    Label {
                        text: "\uf1eb"
                        font.family: faSolidFontFamily
                        font.pixelSize: 20
                        color: "white"
                    }
                    Label {
                        text: "\uf013"
                        font.family: faSolidFontFamily
                        font.pixelSize: 20
                        color: "white"
                    }
                }
            }
        }
    }

    // floated MOB button
    Rectangle {
        id: mobButton
        width: 80
        height: 90
        radius: 10
        color: "red"
        z: 1

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: -10
        anchors.leftMargin: 500

        Column {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottomMargin: 8

            // icon
            Label {
                text: "\ue545"
                font.family: faSolidFontFamily
                font.pixelSize: 32
                color: "white"
                // take full width, then center
                anchors.horizontalCenter: parent.horizontalCenter
            }

            // text
            Label {
                text: "MOB"
                font.pixelSize: 22
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: console.log("Man Overboard triggered")
            cursorShape: Qt.PointingHandCursor
        }
    }
}
