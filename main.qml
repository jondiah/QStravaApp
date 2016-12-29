import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Strava 2")

    Rectangle {
        anchors.fill: parent
        color: "pink"
    }


    ListView {
        id: list
        width: 640
        height: 480
        model: activityModel

        delegate: Rectangle {
            width: 640
            height: 50
            border.color: "orange"
            border.width: 2

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: model.modelData.name
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                text: (model.modelData.distance/1000).toFixed(2) + "km"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: model.modelData.name = "nisse"
            }
        }
    }
}
