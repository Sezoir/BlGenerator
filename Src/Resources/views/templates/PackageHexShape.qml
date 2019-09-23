import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Shapes 1.12

Item {

    // Property for colors
    property color backgroundColor: "lightblue"
    property color borderColor: "black"

    // Properties for changing shape based on percentage
    property real bodyHeight: 0.5
    property real lowerCornerTrigHeight: 0.5

    property real lowerCornerTrigWidth: 0.15
    property real lowerMiddleWidth: 0.7

    // Private properties
    QtObject {
        id: internal

        // Sizes of vertices
        property real bodyHeight: root.bodyHeight*root.height
        property real lowerCornerTrigHeight: root.lowerCornerTrigHeight*root.height

        property real lowerCornerTrigWidth: root.lowerCornerTrigWidth*root.width
        property real lowerMiddleWidth: root.lowerMiddleWidth*root.width

        // Starting positions for drawing
        property real drawStartX: 0
        property real drawStartY: 0
    }

    id: root

    Shape {
        id: shape
        anchors.fill: parent

        ShapePath {
            id: shapePath
            strokeWidth: 2
            strokeColor: borderColor
            strokeStyle: ShapePath.SolidLine
            fillColor: rarityColor

            startX: internal.drawStartX
            startY: internal.drawStartY



            PathLine {
                id: nodeOne
                x: internal.drawStartX + root.width
                y: internal.drawStartY
            }
            PathLine {
                id: nodeTwo
                x: nodeOne.x
                y: nodeOne.y + internal.bodyHeight
            }
            PathLine {
                id: nodeThree
                x: nodeTwo.x - internal.lowerCornerTrigWidth
                y: nodeTwo.y + internal.lowerCornerTrigHeight
            }
            PathLine {
                id: nodeFour
                x: nodeThree.x - internal.lowerMiddleWidth
                y: nodeThree.y
            }
            PathLine {
                id: nodeFive
                x: internal.drawStartX
                y: nodeFour.y - internal.lowerCornerTrigHeight
            }
            PathLine {
                id: nodeSix
                x: internal.drawStartX
                y: internal.drawStartY
            }
        }
    }



}
