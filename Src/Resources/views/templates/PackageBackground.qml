import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Shapes 1.12

import Fluid.Controls 1.0 as FluidControls

Item {
    // Type icon
    property string iconUrl: "../../assets/images/Pistol.ico"

    // Extension length and animation properties
    property bool extended: false
    property int extensionLength: 50
    property int animationDuration: 400

    // Color properties
    property color rarityColor : "Orange"
    property color backgroundColor: "Navy"

    // Properties for changing shape based on percentage
    property real upperCornerTrigWidth: 0.05
    property real upperCornerMiddleWidth: 0.15
    property real upperMiddleWidth: 0.5

    property real upperCornerTrigHeight: 0.05
    property real upperCornerMiddleHeight: 0.1
    property real bodyHeight: 0.78
    property real lowerCornerTrigHeight: 0.07

    property real lowerCornerTrigWidth: 0.07
    property real lowerMiddleTrigWidth: 0.06
    property real lowerMiddleIndentWidth: 0.16

    property real lowerMiddleTrigHeight: 0.06

    QtObject {
        id:internal

        // Set a constant default height
        Component.onCompleted:  {
            defaultHeight = defaultHeight
        }

        // Default height of object on creation
        property real defaultHeight: root.height

        // Value of y to extend to for the node
        property real extensionY: upperCornerTrigHeight + upperCornerHeight + bodyHeight + extensionLength

        // Default value of y for extension node
        property real defaultY: upperCornerTrigHeight + upperCornerHeight + bodyHeight

        // Properties for sizes of shapes
        property real upperCornerTrigWidth: root.width*root.upperCornerTrigWidth
        property real upperCornerMiddleWidth: root.width*root.upperCornerMiddleWidth
        property real upperMiddleWidth: root.width*root.upperMiddleWidth

        property real upperCornerTrigHeight: defaultHeight*root.upperCornerTrigHeight
        property real upperCornerMiddleHeight: defaultHeight*root.upperCornerMiddleHeight
        property real bodyHeight: defaultHeight*root.bodyHeight
        property real lowerCornerTrigHeight: defaultHeight*root.lowerCornerTrigHeight

        property real lowerCornerTrigWidth: root.width*root.lowerCornerTrigWidth
        property real lowerMiddleTrigWidth: root.width*root.lowerMiddleTrigWidth
        property real lowerMiddleIndentWidth: root.width*root.lowerMiddleIndentWidth

        property real lowerMiddleTrigHeight: defaultHeight*root.lowerMiddleTrigHeight

        // Set permanent height of corners
        property int upperCornerHeight: 30

        // Remainder of lower width
        property real lowerWidths: (1-2*root.lowerCornerTrigWidth-2*root.lowerMiddleTrigWidth-root.lowerMiddleIndentWidth)/2

        // Starting positions for drawing
        property real drawStartX: 0
        property real drawStartY: internal.upperCornerTrigHeight + internal.upperCornerMiddleHeight
    }

    id: root

    // Default state
    state: "DEFAULT"

//    MouseArea {
//        anchors.fill: parent
//        onPressed: root.state = "EXTENDED"
//        onReleased: root.state = "DEFAULT"
//    }

    states: [
        State {
            name: "EXTENDED"
            PropertyChanges {
                id: extendedPropNode
                target: nodeTen
                y: internal.extensionY
            }
            PropertyChanges {
                id: extendedPropHeight
                target: root
                height: internal.defaultHeight + extensionLength
            }

        },
        State {
            name: "DEFAULT"
            PropertyChanges {
                id: defaultPropNode
                target: nodeTen
                y: internal.defaultY
            }
            PropertyChanges {
                id: defaultPropHeight
                target: root
                height: internal.defaultHeight
            }
        }

    ]

    transitions: [
        Transition {
            from: "DEFAULT"
            to: "EXTENDED"
            ParallelAnimation {
                PropertyAnimation {
                    property: "y"
                    duration: animationDuration
                }
                PropertyAnimation {
                    property: "height"
                    duration: animationDuration
                }
                AnchorAnimation {
                    duration: animationDuration
                }
            }
        },
        Transition {
            from: "EXTENDED"
            to: "DEFAULT"
            ParallelAnimation {
                PropertyAnimation {
                    property: "y"
                    duration: animationDuration
                }
                PropertyAnimation {
                    property: "height"
                    duration: animationDuration
                }
                AnchorAnimation {
                    duration: animationDuration
                }
            }

        }
    ]

    Shape {
        id: shape
        anchors.fill: parent

        anchors.bottomMargin: -typeIconBackground.height
        ShapePath {
            id: shapePath
            strokeWidth: 2
            strokeColor: "Black"
            strokeStyle: ShapePath.SolidLine
            fillColor: rarityColor

            startX: internal.drawStartX
            startY: internal.drawStartY



            PathLine {
                id: nodeOne
                x: internal.drawStartX
                y: internal.drawStartY - internal.upperCornerMiddleHeight
            }
            PathLine {
                id: nodeTwo
                x: nodeOne.x + internal.upperCornerTrigWidth
                y: nodeOne.y - internal.upperCornerTrigHeight
            }
            PathLine {
                id: nodeThree
                x: nodeTwo.x + internal.upperCornerMiddleWidth
                y: nodeTwo.y
            }
            PathLine {
                id: nodeFour
                x: nodeThree.x + internal.upperCornerTrigWidth
                y: nodeThree.y + internal.upperCornerTrigHeight
            }
            PathLine {
                id: nodeFive
                x: nodeFour.x + internal.upperMiddleWidth
                y: nodeFour.y
            }
            PathLine {
                id: nodeSix
                x: nodeFive.x + internal.upperCornerTrigWidth
                y: nodeFive.y - internal.upperCornerTrigHeight
            }
            PathLine {
                id: nodeSeven
                x: nodeSix.x + internal.upperCornerMiddleWidth
                y: nodeSix.y
            }
            PathLine {
                id: nodeEight
                x: (nodeSeven.x + internal.upperCornerTrigWidth).toFixed()
                y: nodeSeven.y + internal.upperCornerTrigHeight
            }
            PathLine {
                id: nodeNine
                x: nodeEight.x
                y: nodeEight.y + internal.upperCornerMiddleHeight
            }
            PathLine {
                id: nodeTen
                x: nodeNine.x
                y: nodeNine.y + internal.bodyHeight
            }
            PathLine {
                id: nodeEleven
                x: nodeTen.x - internal.lowerCornerTrigWidth
                y: nodeTen.y + internal.lowerCornerTrigHeight
            }
            PathLine {
                id: nodeTwelve
                x: nodeEleven.x - root.width*internal.lowerWidths
                y: nodeEleven.y
            }
            PathLine {
                id: nodeThirteen
                x: nodeTwelve.x - internal.lowerMiddleTrigWidth
                y: nodeTwelve.y - internal.lowerMiddleTrigHeight
            }
            PathLine {
                id: nodeFourteen
                x: nodeThirteen.x - internal.lowerMiddleIndentWidth
                y: nodeThirteen.y
            }
            PathLine {
                id: nodeFifthteen
                x: nodeFourteen.x - internal.lowerMiddleTrigWidth
                y: nodeFourteen.y + internal.lowerMiddleTrigHeight
            }
            PathLine {
                id: nodeSixteen
                x: nodeFifthteen.x - root.width*internal.lowerWidths
                y: nodeFifthteen.y
            }
            PathLine {
                id: nodeSeventeen
                x: internal.drawStartX
                y: nodeSixteen.y - internal.lowerCornerTrigHeight
            }
            PathLine {
                id: nodeEighteen
                x: internal.drawStartX
                y: internal.drawStartY
            }

        }
    }
    Rectangle {
        id: typeIconBackground
        width: internal.lowerMiddleIndentWidth + 2*internal.lowerMiddleTrigWidth
        height: 45
        color: backgroundColor
        border.color: "Black"
        border.width: 2
        anchors.horizontalCenter: parent.horizontalCenter
        y: nodeThirteen.y - 2
        z: -5

        FluidControls.Icon {
            source: Qt.resolvedUrl(iconUrl)//FluidControls.Utils.iconUrl("navigation/chevron_left")
            size: 400
            anchors.fill: parent
            anchors.topMargin: 10
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.bottomMargin: 3
        }
    }
}





