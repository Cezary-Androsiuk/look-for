import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    required property var file
    readonly property int delegateHeight: 80

    readonly property var green: Qt.rgba(102/255, 255/255, 102/255, 1);
    readonly property var white: Qt.rgba(0.8, 0.8, 0.8, 1)

    Item{
        anchors{
            fill: parent
            margins: 5
        }
        clip: true

        Rectangle{
            id: buttonBackground
            anchors.fill: parent
            color: "transparent"
            border.color: white
            border.width: 1
            radius: 10
            clip: true

            TabButton{
                anchors.fill: parent
                checkable: false

                onClicked: {
                    buttonBackground.border.color = green
                    file.open()
                }
            }
        }

        Label{
            id: fileNameLabel
            anchors{
                left: parent.left
                top: parent.top
                right: parent.right
                margins: 5
            }
            wrapMode: "WrapAnywhere"
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft
            text: file.fileName

            font.bold: true
            font.pixelSize: 18
        }

        Label{
            id: pathLabel
            anchors{
                left: parent.left
                top: fileNameLabel.bottom
                right: parent.right
                margins: 5
            }
            wrapMode: "WrapAnywhere"
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft
            text: file.path

            font.pixelSize: 12
        }

    }
}
