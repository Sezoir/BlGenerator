import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Shapes 1.12

Item {
    // Some base alias
//    property alias extensionNode: nodeSix
//    property alias shape: shape
//    property real extensionY: nodeFive.y + internal.bodyHeight + extensionLength

    // Extension length and animation properties
    property bool extended: false
    property int extensionLength: 50
    property int animationDuration: 400

    // Color property
    property color backgroundColor: "LightBlue"

    // Properties for changing shape based on percentage
    property real upperCornerWidth: 0.2
    property real upperMiddleWidth: 0.5
    property real upperMiddleTrigWidth: 0.05

    property real upperMiddleTrigHeight: 0.05
    property real bodyHeight: 0.85
    property real lowerCornerTrigHeight: 0.1

    property real lowerCornerTrigWidth: 0.09
    property real lowerMiddleIndentWidth: 0.19
    property real lowerMiddleTrigWidth: 0.08

    property real lowerMiddleTrigHeight: 0.08

    // Private properties
    QtObject {
        id: internal

        // Set a constant default height
        Component.onCompleted:  {
            defaultHeight = defaultHeight
        }

        // Default height of object on creation
        property real defaultHeight: root.height

        // Value of y to extend to for the node
        property real extensionY: upperMiddleTrigHeight + bodyHeight + extensionLength

        // Default value of y for extension node
        property real defaultY: upperMiddleTrigHeight + bodyHeight

        // Properties for sizes of shapes
        property real upperCornerWidth: root.width*root.upperCornerWidth
        property real upperMiddleWidth: root.width*root.upperMiddleWidth
        property real upperMiddleTrigWidth: root.width*root.upperMiddleTrigWidth

        property real upperMiddleTrigHeight: defaultHeight*root.upperMiddleTrigHeight
        property real bodyHeight: defaultHeight*root.bodyHeight
        property real lowerCornerTrigHeight: defaultHeight*root.lowerCornerTrigHeight

        property real lowerCornerTrigWidth: root.width*root.lowerCornerTrigWidth
        property real lowerMiddleIndentWidth: root.width*root.lowerMiddleIndentWidth
        property real lowerMiddleTrigWidth: root.width*root.lowerMiddleTrigWidth

        property real lowerMiddleTrigHeight: defaultHeight*root.lowerMiddleTrigHeight

        // Remainder of lower width
        property int lowerWidths: (root.width-2*internal.lowerCornerTrigWidth-2*lowerMiddleTrigWidth-lowerMiddleIndentWidth) / 2

        // Starting positions for drawing
        property int drawStartX: 0
        property int drawStartY: internal.upperMiddleTrigHeight
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
                target: nodeSix
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
                target: nodeSix
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

        ShapePath {
            strokeWidth: 2
            strokeColor: "Black"
            strokeStyle: ShapePath.SolidLine
            fillColor: backgroundColor

            startX: internal.drawStartX
            startY: internal.drawStartY



            PathLine {
                id: nodeOne
                x: internal.drawStartX + internal.upperCornerWidth
                y: internal.drawStartY
            }
            PathLine {
                id: nodeTwo
                x: nodeOne.x + internal.upperMiddleTrigWidth
                y: nodeOne.y - internal.upperMiddleTrigHeight
            }
            PathLine {
                id: nodeThree
                x: nodeTwo.x + internal.upperMiddleWidth
                y: nodeTwo.y
            }
            PathLine {
                id: nodeFour
                x: nodeThree.x + internal.upperMiddleTrigWidth
                y: nodeThree.y + internal.upperMiddleTrigHeight
            }
            PathLine {
                id: nodeFive
                x: (nodeFour.x + internal.upperCornerWidth).toFixed()
                y: nodeFour.y
            }
            PathLine {
                id: nodeSix
                x: nodeFive.x
                y: nodeFive.y + internal.bodyHeight
            }
            PathLine {
                id: nodeSeven
                x: nodeSix.x - internal.lowerCornerTrigWidth
                y: nodeSix.y + internal.lowerCornerTrigHeight
            }
            PathLine {
                id: nodeEight
                x: nodeSeven.x - internal.lowerWidths
                y: nodeSeven.y
            }
            PathLine {
                id: nodeNine
                x: nodeEight.x - internal.lowerMiddleTrigWidth
                y: nodeEight.y - internal.lowerMiddleTrigHeight
            }
            PathLine {
                id: nodeTen
                x: nodeNine.x - internal.lowerMiddleIndentWidth
                y: nodeNine.y
            }
            PathLine {
                id: nodeEleven
                x: nodeTen.x - internal.lowerMiddleTrigWidth
                y: nodeTen.y + internal.lowerMiddleTrigHeight
            }
            PathLine {
                id: nodeTwelve
                x: nodeEleven.x - internal.lowerWidths
                y: nodeEleven.y
            }
            PathLine {
                id: nodeThirteen
                x: internal.drawStartX
                y: nodeTwelve.y - internal.lowerCornerTrigHeight
            }
            PathLine {
                id: nodeFifthteen
                x: internal.drawStartX
                y: internal.drawStartY
            }

        }
    }

}
