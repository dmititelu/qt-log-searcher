import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.2
import Controllers 1.0
import QtQuick.Layouts 1.3

Window {

    property QtObject controller: LogSystemController {}
    visible: true
    width: 640
    height: 480
    title: qsTr("uniqFEED HR-186780 Assessment")

    color: "#2E2F30"

    Row {
        id: r_filter
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }

        height: 35
        spacing: 10

        Label {
            text: qsTr("Filter Logs")
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: ti_filter_term
            width: 150
            height: parent.height
            onAccepted: console.debug("Accepted new filter term %0".arg(text))
            enabled: !controller.logError
            onDisplayTextChanged:
            {
                controller.filterBy = displayText
            }
        }
    }

    GroupBox
    {
        id: gb_results
        label: Label {
            text: qsTr("Results View")
            color: "white"
        }

        anchors {
            top: r_filter.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }

        Item
        {
            id: i_sessionCount
            width: parent.width/4
            height: parent.height/10
            Text {
                text: qsTr("Log count session")
                color: "white"
            }
        }

        Item
        {
            id: i_fieldNumber
            width: parent.width/4
            height: parent.height/10
            anchors.left: i_sessionCount.right
            Text {
                text: qsTr("FieldNumber")
                color: "white"
            }
        }

        Item
        {
            id: i_Type
            width: parent.width/4
            height: parent.height/10
            anchors.left: i_fieldNumber.right
            Text {
                text: qsTr("Type")
                color: "white"
            }
        }

        Item
        {
            id: i_description
            width: parent.width/4
            height: parent.height/10
            anchors.left: i_Type.right
            Text {
                text: qsTr("Description")
                color: "white"
            }
        }

        ListView {
            id: listView

            focus: true
            currentIndex: 0
            y: parent.height/10
            width: parent.width
            height: parent.height - parent.height/10

            interactive: true
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {
                    active: true
                    }

            model: controller.logModel

            delegate: ItemDelegate {
                width: parent.width
                Item
                {
                    id: i_logSessionCount
                    width: parent.width/4
                    Text
                    {
                        id: t_logSessionCount
                        text: logSessionCount
                        color: "white"
                    }
                }

                Item
                {
                    id: i_logFieldNumber
                    width: parent.width/4
                    anchors.left: i_logSessionCount.right
                    Text
                    {
                        id: t_logFieldNumber
                        text: logFieldNumber
                        color: "white"
                    }
                }

                Item
                {
                    id: i_logType
                    width: parent.width/4
                    height: parent.height/10
                    anchors.left: i_logFieldNumber.right
                    Text
                    {
                        id: t_logType
                        text: logType
                        color: "white"

                        anchors.left: i_Type.left
                    }
                }


                Item
                {
                    id: i_logLabel
                    width: parent.width/4
                    anchors.left: i_logType.right
                    Text
                    {
                        id: t_logLabel
                        text: logLabel
                        width: parent.width
                        elide: Text.ElideRight

                        color: "white"
                        anchors.left: i_description.left
                    }
                }
            }
        }

        visible: !controller.logError
    }

    Text {
        id: name
        text: "Error reading log file"
        color: "red"
        visible: controller.logError

        anchors {
            top: r_filter.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }
}
