import QtQuick 2.0
import QtQuick.Scene3D 2.0
import QtQuick.Controls 2.1

Item {
    id: root
    width: 1280
    height: 700

    //version property
    property string version: "3.0"

    //planet list show flag
    property bool showPlanetList: false

    //frame propery
    property bool showDataFrameInfo: false

    //focused planet
    property int currentSelectedObject: 0

    //3d viewport
    Scene3D {
        id: scene
        anchors.fill: parent
        aspects: ["render", "logic", "input"]
        focus: true
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

        //from c++ code
        SolarEntityMain {
            id: solarSystem
            Component.onCompleted: {
                solarSystem.setSize(root.width, root.height)
                solarSystem.inputSettings.setEventSource(root)
            }
        }
    }   

    //slider frame
    SolarFrame {
        id: speedSliderFrame
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 5
        height: 400
        width: 50
        radius: 4

        Slider {
            id: speedSlider
            orientation: Qt.Vertical
            anchors.fill: parent
            from: 0
            to: 100
            value: 50
            onValueChanged: {
                solarSystem.animator.setSolarSpeed(value);
            }
        }
    }

    //take a solar screenshot
    TransparentButton {
        id: screenButton
        anchors.right: parent.right
        anchors.top: speedSliderFrame.bottom
        anchors.topMargin: 5
        anchors.rightMargin: 5
        radius: 4
        height: 50
        width: 50
        toolTipVisibility: true
        toolTipText: "Screenshot"
        source: "qrc:/Resources/Images/screen_icon.png"
        onClicked: {
            root.grabToImage(function(result) {
                result.saveToFile("SolarSystemScreen.png");
            });
        }
    }

    //solar object info
    Info {
        id: infoText
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: speedSliderFrame.left
        anchors.rightMargin: 5
        width: 600
        height: speedSliderFrame.height + 100
    }

    //extra speed button
    TransparentButton {
        id: extraButton
        anchors.right: parent.right
        anchors.bottom: speedSliderFrame.top
        anchors.rightMargin: 5
        anchors.bottomMargin: 5
        toolTipVisibility: true
        toolTipText: "Extra Speed"
        radius: 4
        height: 50
        width: 50

        Text {
            id: extraText
            color: "#ffffff"
            anchors.fill: parent
            font.family: "Comic Sans MS"
            font.bold: true
            font.italic: true
            font.pointSize: 12
            styleColor: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("x") + solarSystem.animator.extraSpeed.toString()
        }

        onClicked: solarSystem.animator.changeExtraSpeed()
    }

    //date label
    SolarFrame {
        id: timeFrame
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 5
        radius: 4
        width: 200
        height: 50

        DateText {
            id: timeLabel
            text: "Actual time"
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }

        //show current solar time
        DateText {
            id: solarTime
            anchors.top: timeLabel.bottom

            //show time to label
            function showTime() {
                var solarDate = solarSystem.solarDate;
                var hours = solarDate.getUTCHours();
                var minutes = solarDate.getUTCMinutes();
                var days  = solarDate.getUTCDate();
                var month = solarDate.getUTCMonth() + 1;
                var year = solarDate.getUTCFullYear();

                var str = "";

                if (hours.toString().length == 1)
                    str += "0"

                str += hours.toString()
                str += ":"

                if (minutes.toString().length == 1)
                    str += "0"

                str += minutes.toString()
                str += " "

                if (days.toString().length == 1)
                    str += " "

                str += days.toString()
                str += "/"

                if (month.toString().length == 1)
                    str += "0"

                str += month.toString()
                str += "/"
                str += year.toString()

                return str
            }

            text: showTime()
        }
    }

    //left side controls
    Controls {
        id: controlElements
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 5
        elementWidth: 80
        elementHeight: 100

        //slot
        onPlanetButtonClicked: {
            showPlanetList = !showPlanetList;

            if (showPlanetList) {
                showAnimation.start();
                planetsView.visible = true;
            }
            else {
                unshowAnimation.start()
            }
        }

        //slot
        onInfoButtonClicked: showDataFrameInfoFunc();
    }

    //functions
    function showDataFrameInfoFunc() {
        showDataFrameInfo = !showDataFrameInfo;

        if (showDataFrameInfo)
            dataFrameShowAnimation.start()
        else
            dataFrameUnShowAnimation.start()
    }

    //planets icons
    SolarFrame {
        id: planetsList
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 100
        anchors.leftMargin: 5
        anchors.bottomMargin: 10
        anchors.rightMargin: 5
        radius: 4
        opacity: 0

        //show list
        PropertyAnimation {
            id: showAnimation
            target: planetsList
            property: "opacity"
            to: 1
            duration: 500
        }

        //show list
        PropertyAnimation {
            id: unshowAnimation
            target: planetsList
            property: "opacity"
            to: 0
            duration: 500
            onStopped: planetsView.visible = false
        }

        //all planets
        PlanetList {
            id: planetsView
            anchors.fill: parent
            buttonSize: height - 5
            visible: false
            onClicked:  {
                if (planetsView.focusedPlanet == 0) {
                    extraButton.visible = true
                    infoText.unshowInfo.start()
                }
                else {
                    extraButton.visible = false;
                    infoText.showInfo.start()
                }

                solarSystem.animator.resetExtraSpeed();
                solarSystem.animator.setCameraViewCenter(planetsView.focusedPlanet);

                if (planetsView.focusedPlanet != 0)
                    infoText.text = solarSystem.animator.info;
            }
        }
    }

    //exit button
    TransparentButton {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.topMargin: 5
        toolTipVisibility: false
        radius: 4
        source: "qrc:/Resources/Images/exit_icon.png"
        width: 60
        height: 80
        onClicked: Qt.quit();
    }

    //left frame with data
    SolarFrame {
        id: dataFrame
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: controlElements.right
        anchors.leftMargin: 10
        width: controlElements.height
        height: controlElements.height
        radius: 4
        opacity: 0

        //show list
        PropertyAnimation {
            id: dataFrameShowAnimation
            target: dataFrame
            property: "opacity"
            to: 1
            duration: 500
        }

        //show list
        PropertyAnimation {
            id: dataFrameUnShowAnimation
            target: dataFrame
            property: "opacity"
            to: 0
            duration: 500
        }

        //info text
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: "#ffffff"
            font.italic: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            styleColor: "#ffffff"
            text: qsTr("Solar System v. ") + version +
                  qsTr("\n") +
                  qsTr("\n") +
                  qsTr("Based on Qt Framework with Qt3D technology.\n") +
                  qsTr("For education only.\n") +
                  qsTr("Some features used from\nQt Planet QML example.") +
                  qsTr("\n") +
                  qsTr("Some textures used from:\nhttp://www.solarsystemscope.com.") +
                  qsTr("\n") +
                  qsTr("\n") +
                  qsTr("Created by Nikita Chernyaev\naka Instand in 2017,\n") +
                  qsTr("Source code available at:\nhttps://github.com/Instand/SolarSystem\n") +
                  qsTr("\nThanks to Emerald for advises\nand Qt Company for Qt.")
        }

    }

    //object text
    Text {
        id: planetText
        anchors.top: timeFrame.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        width: 200
        height: 60
        font.pointSize: 30
        font.wordSpacing: 2
        font.bold: true
        font.italic: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        text: solarSystem.animator.solarObjectString
        font.family: "Century Gothic"
    }
}
