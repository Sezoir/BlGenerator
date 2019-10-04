import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Shapes 1.12
import Fluid.Controls 1.0 as FluidControls

Item {
    // Base properties
    property string packageName: "NAME NOT SET"
    property int playerNum: 0
    property int level: 0
    property string rarity: "N/A"
    property string manufacturer: "N/A"

    // Readonly properties
    readonly property real contentWidth: middle.width

    // Extension length and animation properties
    property bool extended: false
    property int extensionLength: middle.height < middle.contentHeight ? (middle.contentHeight - middle.height) : 0 //100
    property int animationDuration: 150

    // Color properties
    property color backgroundColor: "#035afc"
    property color foregroundColor: "Lightblue"
    property color rarityColor : "Orange"

    // Default storage location for properties
    default property alias content: objectProperties.children

    //@todo need to fix opacity animation not correctly triggering for expandIcon
    id: root
    z: extended ? 3 : 0

    // Unbind initial value
    Component.onCompleted: {
        extensionLength = extensionLength;
    }

    MouseArea {
        id: mouseArea
        anchors.fill: packBackground
        z: 3
        hoverEnabled: true
        propagateComposedEvents: true
//        onPressed: root.state = "EXTENDED"
//        onReleased: root.state = "DEFAULT"
    }

    states: [
        State {
            name: "EXTENDED"
            when: mouseArea.containsMouse
            PropertyChanges {
                id: extendedPropBackHeight
                target: packBackground
                state: "EXTENDED"
            }
            PropertyChanges {
                id: extendedPropForeHeight
                target: packForeground
                state: "EXTENDED"
            }
            PropertyChanges {
                id: extendedIconOpacity
                target: expandIcon
                opacity: 0.0
            }
            PropertyChanges {
                id: extendedIconVisible
                target: expandIcon
                visible: false
            }
        },
        State {
            name: "DEFAULT"
            PropertyChanges {
                id: defaultPropBackHeight
                target: packBackground
                state: "DEFAULT"
            }
            PropertyChanges {
                id: defaultPropForeHeight
                target: packForeground
                state: "DEFAULT"
            }
            PropertyChanges {
                id: defaultIconVisble
                target: expandIcon
                visible: true
            }
            PropertyChanges {
                id: defaultIconOpacity
                target: expandIcon
                opacity: 1.0
            }
        }

    ]

    transitions: [
        Transition {
            from: "DEFAULT"
            to: "EXTENDED"
            ParallelAnimation {
                PropertyAnimation {
                    property: "state"
                    duration: animationDuration
                }
                AnchorAnimation {
                    duration: animationDuration
                }
            }
            SequentialAnimation {
                OpacityAnimator {
                    target: expandIcon
                    duration: animationDuration
                    easing.type: Easing.InOutQuad
                }
                PropertyAnimation {
                    target: expandIcon
                    property: "visible"
                    duration: 0
                }
            }
        },
        Transition {
            from: "EXTENDED"
            to: "DEFAULT"
            ParallelAnimation {
                PropertyAnimation {
                    property: "state"
                    duration: animationDuration
                }
                AnchorAnimation {
                    duration: animationDuration
                }
                SequentialAnimation {
                    PropertyAnimation {
                        target: expandIcon
                        property: "visible"
                        duration: 0
                    }
                    OpacityAnimator {
                        target: expandIcon
                        duration: animationDuration
                        easing.type: Easing.InOutQuad
                    }
                }
            }

        }
    ]

    PackageBackground {
        id: packBackground
        z: 0
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: parent.height
        rarityColor: root.rarityColor
        backgroundColor: root.backgroundColor

        animationDuration: root.animationDuration
        extensionLength: root.extensionLength
    }

    FluidControls.HeadlineLabel {
        id: playerText
        anchors {
            top: packBackground.top
            bottom: packForeground.top
            bottomMargin: -packForeground.upperMiddleTrigHeight*packForeground.height
            left: packBackground.left
            leftMargin: packBackground.upperCornerTrigWidth*packBackground.width
        }
        width: packBackground.upperCornerMiddleWidth*packBackground.width

        text: playerNum
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        style: Text.Outline
        styleColor: "Black"
        color: "white"
    }

    FluidControls.HeadlineLabel {
        id: levelText
        anchors {
            top: packBackground.top
            bottom: packForeground.top
            bottomMargin: -packForeground.upperMiddleTrigHeight*packForeground.height
            right: packBackground.right
            rightMargin: packBackground.upperCornerTrigWidth*packBackground.width
        }
        width: packBackground.upperCornerMiddleWidth*packBackground.width

        text: level
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        style: Text.Outline
        styleColor: "Black"
        color: "white"
    }

    RowLayout {

        anchors {
            top: packBackground.top
            topMargin: packBackground.upperCornerTrigHeight*packBackground.height + 3
            bottom: packForeground.top
            bottomMargin: 3
            left: playerText.right
            leftMargin: packBackground.upperCornerTrigWidth*packBackground.width + 2
            right: levelText.left
            rightMargin: packBackground.upperCornerTrigWidth*packBackground.width + 2

        }
        FluidControls.SubheadingLabel {
            Layout.fillHeight: true
            Layout.fillWidth: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text: "Player"
            style: Text.Outline
            styleColor: "Black"
            color: "white"
        }
        FluidControls.SubheadingLabel {
            Layout.fillHeight: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            text: "Level"
            style: Text.Outline
            styleColor: "Black"
            color: "white"
        }
    }

    PackageForeground {
        id: packForeground
        z: 0
        anchors {
            top: packBackground.top
            left: packBackground.left
            right: packBackground.right

            topMargin: 30
            leftMargin: 5
            rightMargin: 5
        }
        height: parent.height - 37
        backgroundColor: root.foregroundColor

        animationDuration: root.animationDuration
        extensionLength: root.extensionLength

        Item {
            anchors.fill: parent
            anchors {
                topMargin: 13
                leftMargin: 10
                rightMargin: 10
                bottomMargin: 10
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                Item {
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 40
                    height: 40
                    FluidControls.HeadlineLabel {
                        anchors.fill: parent
                        text: packageName
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        //fontSizeMode: Text.Fit
                        fontSizeMode: Text.VerticalFit
                        wrapMode: Text.WordWrap
                        style: Text.Outline
                        styleColor: "Black"
                        color: rarityColor
                    }

//                    Rectangle {
//                        anchors.fill: parent
//                        color: "purple"
//                    }
                }
                Flickable {
                    id: middle
                    Layout.preferredWidth: parent.width
                    Layout.fillHeight: true

                    contentHeight: objectProperties.height
                    contentWidth: objectProperties.width

                    //clip: true

                    ColumnLayout {
                        property alias rarityColor: root.rarityColor
                        id: objectProperties

                        anchors {
                            left: parent.left
                            right: parent.right
                            top: parent.top
                        }
                    }
                }
                Item {
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 60

                    RowLayout {
                        anchors.fill: parent

                        PackageHexShape {
                            Layout.preferredHeight: 40
                            Layout.minimumWidth: 10
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignLeft
                            FluidControls.SubheadingLabel {
                                anchors {
                                    top: parent.top
                                    left: parent.left
                                    leftMargin: 5
                                    right: parent.right
                                    rightMargin: 5
                                    bottom: parent.bottom
                                }
                                text: rarity
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.Fit
                                style: Text.Outline
                                styleColor: "Black"
                                color: "white"
                            }
                        }
                        Item {
                            Layout.preferredHeight: 40
                            Layout.preferredWidth: packForeground.lowerMiddleIndentWidth*packForeground.width
                            Layout.alignment: Qt.AlignCenter
                            Layout.fillWidth: false
                            FluidControls.Icon {
                                id: expandIcon
                                size: parent.height
                                anchors.centerIn: parent
                                visible: middle.height < middle.contentHeight + 2
                                opacity: 1
                                source: FluidControls.Utils.iconUrl("hardware/keyboard_arrow_down")
                            }
                        }
                        PackageHexShape {
                            Layout.preferredHeight: 40
                            Layout.minimumWidth: 10
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignRight

                            FluidControls.SubheadingLabel {
                                anchors {
                                    top: parent.top
                                    left: parent.left
                                    leftMargin: 5
                                    right: parent.right
                                    rightMargin: 5
                                    bottom: parent.bottom
                                }
                                text: manufacturer
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.Fit
                                style: Text.Outline
                                styleColor: "Black"
                                color: "white"
                            }
                        }
                    }
                }
            }

        }
    }

//    PackageForeground {
//        id: packForeground
//        anchors.fill: parent
//        anchors {
//            topMargin: 30
//            leftMargin: 5
//            rightMargin: 5
//            bottomMargin: 5
//        }
//        backgroundColor: root.backgroundColor
//        opacity: 0.8
//        extended: root.extended
//        animationDuration: root.animationDuration
//        extensionLength: root.extensionLength
//        z: 1

//        Item {
//            id: itemProperty

//            anchors {
//                top: parent.top
//                bottom: parent.bottom
//                left: parent.left
//                right: parent.right
//                topMargin: 30
//                bottomMargin: 30
//                leftMargin: 15
//                rightMargin: 15
//            }

//            Item {
//                id: nameProperty
//                height: 30

//                anchors {
//                    top: parent.top
//                    left: parent.left
//                    right: parent.right
//                }

//                Rectangle {
//                    id: background
//                    z: -1
//                    anchors.fill: parent
//                    color: "#31353a"
//                    opacity: 0.8
//                }

//                FluidControls.SubheadingLabel {
//                    height: parent.height
//                    width: parent.width
//                    text: packageName
//                    verticalAlignment: Text.AlignVCenter
//                    horizontalAlignment: Text.AlignHCenter

//                }
//            }

//            Flickable {
//                property real weight: 40
//                id: contentProperty
//                anchors {
//                    top: nameProperty.bottom
//                    left: parent.left
//                    right: parent.right
//                    topMargin: 10
//                }
//                height: 40//(packForeground.bodyHeight*packForeground.height) - nameProperty.height - bottomProperty.height

//                contentHeight: content.height
//                contentWidth: content.width
//                clip: true

//                ColumnLayout {
//                    id: content
//                    anchors {
//                        top: parent.top
//                        left: parent.left
//                        right: parent.right
//                    }
//                }
//            }
//            Item {
//                id: bottomProperty

//                anchors {
//                    top: contentProperty.bottom
//                    left: parent.left
//                    right: parent.right
//                    bottom: parent.bottom
//                    topMargin: 15
//                }
//                Rectangle {
//                    anchors.fill: parent
//                    color: "red"
//                }
//            }
//        }
//    }
}
