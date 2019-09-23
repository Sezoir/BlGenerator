import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtGraphicalEffects 1.0
import Fluid.Controls 1.0 as FluidControls

import "../templates"

Item {
    id: root
    width: parent.width
    height: parent.height
    anchors.fill: parent


    Rectangle {
        id: rect
        x: 40
        y: 500
        width: 40
        height: 40
        color: "red"

        PropertyAnimation on y {duration: 1000; to: 0}
    }

    Rectangle {
//        anchors.left: rect.right
//        anchors.top: rect.top
//        width: 40
//        height: 40
        anchors.fill: rect
        anchors.leftMargin: -rect.width

        color: "purple"
        z: 3
    }

//    PackageTemplate {
//        id: testone
//        x: 500
//        y: 100
//        height: 320
//        width: 250
//    }
//    Rectangle {
//        height: 40
//        width: 40
//        color: "red"
//        anchors.top: testone.bottom
//        anchors.left: testone.left
//    }

    PackageWeapon {
        id: test
        x: 900
        y: 100
        width: 250
        height: 320

//        PackageProperty {
//            id: pack
//            Layout.height: 20
//            width: parent.width
//        }
//        PackageProperty {
//            id: packq
//            key: "tedsffsd"
//            value: "10d20"
//            Layout.preferredWidth: test.contentWidth
//        }
//        PackageProperty {
//            id: packw
//            key: "tedsffsd"
//            value: "10d20"
//            height: 20
//            Layout.preferredWidth: test.contentWidth
//        }
//        PackageProperty {
//            id: packe
//            key: "tedsffsd"
//            value: "10d20"
//            height: 20
//            Layout.preferredWidth: test.contentWidth
//        }
//        PackageProperty {
//            id: packr
//            key: "tedsffsd"
//            value: "10d20"
//            height: 20
//            Layout.preferredWidth: test.contentWidth
//        }
//        PackageProperty {
//            id: packt
//            key: "tedsffsd"
//            value: "10d20"
//            height: 20
//            Layout.preferredWidth: test.contentWidth
//        }
//        PackageProperty {
//            id: packy
//            key: "tedsffsd"
//            value: "10d20"
//            height: 20
//            Layout.preferredWidth: test.contentWidth
//        }
//        PackageProperty {
//            id: packu
//            key: "tedsffsd"
//            value: "10d20"
//            height: 20
//            Layout.preferredWidth: test.contentWidth
//        }


//        Rectangle {
//            width: 40
//            Layout.preferredHeight: 40
//            color: "red"
//        }
//        Rectangle {
//            width: 40
//            Layout.preferredHeight: 40
//            color: "blue"
//        }


    }
}
