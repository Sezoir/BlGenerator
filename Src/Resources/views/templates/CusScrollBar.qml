import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import Fluid.Controls 1.0 as FluidControls

Item {
    // Some base properties
    property var target: null
    property real position: 0
    property real pageSize: scrollBar.height/target.contentHeight
    property var orientation: Qt.Vertical
    property var side: Qt.RightEdge
    property int thickness: 20

    id: scrollBar
    z: target.z + 1

    // Set the correct thickness of bar based on orientation
    height: (orientation == Qt.Vertical) ? undefined : thickness
    width: (orientation == Qt.Vertical) ? thickness : undefined

    // Bind to correct side
    anchors {
        top: (side == Qt.RightEdge || side == Qt.LeftEdge || side == Qt.TopEdge) ? target.top : undefined
        bottom: (side == Qt.RightEdge || side == Qt.LeftEdge || side == Qt.BottomEdge) ? target.bottom : undefined
        left: (side == Qt.BottomEdge || side == Qt.LeftEdge || side == Qt.TopEdge) ? target.left : undefined
        right: (side == Qt.RightEdge || side == Qt.BottomEdge || side == Qt.TopEdge) ? target.right : undefined
    }

    // A light semi-transparant background
    Rectangle {
        id: background
        z: 1
        anchors.fill: parent
        radius: orientation == Qt.Vertical ? (width/2 - 1) : (height/2 - 1)
        color: "white"
        border.color: "black"
        border.width: 1
        opacity: 0.3
        }

    // Size bar to required size based on orientation
    Rectangle {
        x: orientation == Qt.Vertical ? 1 : (scrollBar.position * (scrollBar.width-2) + 1)
        y: 30//orientation == Qt.Vertical ? (scrollBar.position * (scrollBar.height - 2) + 1) : 1
        z: 2
        width: orientation == Qt.Vertical ? (parent.width - 2) : (scrollBar.pageSize * (scrollBar.width - 2))
        height: orientation == Qt.Vertical ? (scrollBar.pageSize * (scrollBar.height - 2)) : (parent.height - 2)
        radius: orientation == Qt.Vertical ? (width/2 - 1) : (height/2 - 1)
        color: "black"
        opacity: 0.7

        MouseArea {
            anchors.fill: parent
            onClicked: console.log("helloworld!")
            drag.target: parent

            drag.axis: (orientation == Qt.Vertical) ? Drag.YAxis : Drag.XAxis
            drag.minimumX: 0
            drag.minimumY: 0
            drag.maximumX: scrollBar.width - width
            drag.maximumY: scrollBar.height - height

            onPositionChanged: {
                if((pressedButtons == Qt.LeftButton) && (orientation == Qt.Vertical))
                {
                    scrollBar.position += y/scrollBar.height
                    //target.contentY = parent.y * target.contentHeight / scrollBar.height
                }
                else if((pressedButtons == Qt.LeftButton) && (orientation == Qt.Horizontal))
                {
                    target.contentX = parent.x * target.contentWidth / scrollBar.width
                }
            }
        }
    }



//    Timer {
//        property int scrollAmount

//        id: timer
//        repeat: true
//        interval: 20
//        onTriggered: {
//            target.contentY = Math.max(
//                        0, Math.min(
//                           target.contentY + scrollAmount,
//                           target.contentHeight - target.heigh));
//        }
//    }



}

