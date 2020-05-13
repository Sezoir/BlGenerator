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

    PackageElementProperty {
        id: elementProp
        x: 300
        y: 200
        width: 250
        //height: 50

        elements: {
            "fire" :
            {
               "color" : "red",
               "damage" : "1d6",
               "condition" : "Healthbar",
               "chance" : "16",
               "effect" : "Does something",
               "iconPath" : "/Config/Images/Fire.ico"
            },
            "corrosion" :
            {
                "color" : "green",
                "damage" : "1d6",
                "condition" : "Armour",
                "chance" : "18",
                "effect" : "Does something",
                "iconPath" : "/Config/Images/Fire.ico"
            }
        }


    }


}
