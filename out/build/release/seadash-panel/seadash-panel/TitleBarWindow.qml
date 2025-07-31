import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.VectorImage

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

                MouseArea {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    width: coordRow.implicitWidth
                    height: coordRow.implicitHeight
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        console.log("GPS settings clicked")
                    }

                    Row {
                        id: coordRow
                        spacing: 8

                        VectorImage {
                            anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/icons/images/location-dot-solid-full.svg"
                            width: 22; height: 22
                            fillMode: Image.PreserveAspectFit
                            preferredRendererType: VectorImage.CurveRenderer
                        }
                        Label {
                            anchors.verticalCenter: parent.verticalCenter
                            id: coordLabel
                            text: "50\u00B043.599'N 000\u00B032.461'W"
                            color: "white"
                            font.pixelSize: 22
                        }
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

                    MouseArea {
                        width: 24
                        height: 24
                        onClicked: console.log("Bluetooth icon clicked")
                        cursorShape: Qt.PointingHandCursor
                        VectorImage {
                            anchors.centerIn: parent
                            anchors.fill: parent
                            source: "qrc:/icons/images/bluetooth-brands-solid-full.svg"
                            fillMode: Image.PreserveAspectFit
                            preferredRendererType: VectorImage.CurveRenderer
                        }
                    }

                    MouseArea {
                        width: 24
                        height: 24
                        onClicked: console.log("Wi-Fi icon clicked")
                        cursorShape: Qt.PointingHandCursor

                        VectorImage {
                            anchors.centerIn: parent
                            anchors.fill: parent
                            source: "qrc:/icons/images/wifi-solid-full.svg"
                            fillMode: Image.PreserveAspectFit
                            preferredRendererType: VectorImage.CurveRenderer
                        }
                    }

                    MouseArea {
                        width: 24
                        height: 24
                        onClicked: console.log("Settings icon clicked")
                        cursorShape: Qt.PointingHandCursor

                        VectorImage {
                            anchors.centerIn: parent
                            anchors.fill: parent
                            source: "qrc:/icons/images/gear-solid-full.svg"
                            fillMode: Image.PreserveAspectFit
                            preferredRendererType: VectorImage.CurveRenderer
                        }
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
            VectorImage {
                source: "qrc:/icons/images/person-drowning-solid-full.svg"
                width: 32; height: 32
                fillMode: Image.PreserveAspectFit
                anchors.horizontalCenter: parent.horizontalCenter
                preferredRendererType: VectorImage.CurveRenderer
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
