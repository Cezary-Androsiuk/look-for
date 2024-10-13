import QtQuick
import QtQuick.Controls.Material

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ListView{
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        model: Backend.foundFiles

        delegate: Item{
            width: root.width
            height: 60

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    modelData.open()
                }
            }

            Label{
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                text: modelData.fileName
            }
        }
    }
}
