import QtQuick
import QtQuick.Controls.Material
// import Qt5Compat.GraphicalEffects // maybe this is required for JPG support

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Look For: \"" + Backend.searchPhrase + "\"");

    Material.theme: Material.Dark

    ListView{
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        model: Backend.foundFiles

        delegate: Item{
            id: delegateItem
            width: root.width
            height: 80

            Loader{
                id: loader
                width: parent.width
                height: parent.height

                Component.onCompleted: {
                    var fileDelegateSource;

                    if(modelData.isImage)
                        fileDelegateSource = "delegates/ImageDelegate.qml";
                    else
                        fileDelegateSource = "delegates/PathDelegate.qml";

                    setSource(fileDelegateSource, { file: modelData })
                }

                onLoaded: {
                    item.width = delegateItem.width;
                    var h = item.delegateHeight;
                    delegateItem.height = h;
                    item.height = h;
                }
            }


        }
    }
}
