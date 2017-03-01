import QtQuick 2.7
import QtQuick.Controls 2.1

//root element
Rectangle {
    id: root
    border.color: "white"
    color: "transparent"

    //source ref
    property alias source: image.source

    //click signal
    signal clicked;

    //toolTip help text
    property alias toolTipText: helpText.text
    property alias toolTipWidth: help.width
    property alias toolTipHeight: help.height

    //values
    property real lowOpacity: 0.1
    property real maxOpacity: 0.3

    //tooltip visibility
    property bool toolTipVisibility: false

    //image on Rectangle surface
    Image {
        id: image
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width/1.7
        height: parent.width/1.7
        smooth: true
        mipmap: true
    }

    //opacity white rectangle
    Rectangle {
        id: coloredRECT
        anchors.fill: parent
        color: "white"
        opacity: lowOpacity

        //press area
        MouseArea {
            id: area
            anchors.fill: parent
            hoverEnabled: true

            //click event
            onClicked: {
                root.clicked()
            }

            //press event
            onPressed: {
                coloredRECT.opacity = root.lowOpacity
            }

            //release event
            onReleased: {
                if (area.containsMouse)
                    coloredRECT.opacity = root.maxOpacity
            }

            //enter event
            onEntered: {

                if (root.toolTipVisibility)
                    help.visible = true

                coloredRECT.opacity = root.maxOpacity
            }

            //exit event
            onExited: {
                help.visible = false
                coloredRECT.opacity = root.lowOpacity
            }
        }

        //help text
        ToolTip {
            id: help

            //tooltip item
            background: Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                id: helpText
                color: "white"
                font.pointSize: 12
                font.family: "Helvetica"
                font.weight: Font.Light
            }
        }
    }
}
