import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import Fluid.Controls 1.0 as FluidControls

// Pages
import "pages"

FluidControls.ApplicationWindow  {
    // Set screen limits
    // Note height has to -1 due to issues when minimising application
    property int screenHeight: Screen.height -1
    property int screenWidth: Screen.width

    id: window
    visible: true
    x:0
    y:0
    //width: 640
    //height: 480
    width: screenWidth
    height: screenHeight
    title: qsTr("Bl Generator")

    // Flags for fullscreen whilst allowing minimising application
    flags:  Qt.FramelessWindowHint |
            Qt.WindowMinimizeButtonHint |
            Qt.Window

    initialPage: mainTab

    // Tab bar
    FluidControls.TabbedPage {
            id: mainTab
            title: "Bl Generator"

            actions: [
                FluidControls.Action {
                    icon.source: FluidControls.Utils.iconUrl("action/settings")
                    text: qsTr("Change settings")
                    toolTip: qsTr("Change settings")
                    onTriggered: ;
                },

                FluidControls.Action {
                    icon.source: FluidControls.Utils.iconUrl("action/power_settings_new")
                    text: qsTr("Close application")
                    toolTip: qsTr("Close application")
                    onTriggered: window.close()
                }

            ]

            FluidControls.Tab {
                id: generationTab
                title: "Generation"
                Loader {
                    id: generationLoader
                    width: parent.width
                    height: parent.height
                    source: "pages/Generation.qml"
                    asynchronous: true
                    active: (mainTab.currentIndex == 0) ? true : false
                    visible: (status == Loader.Ready && mainTab.currentIndex == 0) ? true : false
                }
            }

            FluidControls.Tab {
                id: creationTab
                title: "Creation"
                Loader {
                    id: creationLoader
                    width: parent.width
                    height: parent.height
                    source: "pages/Creation.qml"
                    asynchronous: true
                    active: (mainTab.currentIndex == 1) ? true : false
                    visible: (status == Loader.Ready && mainTab.currentIndex == 1) ? true : false
                }
            }
        }

//    Rectangle {
//        color: "red"
//        width: 80
//        height: 80
//        radius: 80
//        x: 0
//        y: 0
//    }

//    Column {
//        x: 300
//        y: 50
//        id: col
//        Button {
//            id: generateButton
//            text: qsTr("Press Me!")
//            onPressed: GenerateController.clicked()
//        }
//        Text {
//            id: someText
//            text: GenerateController.loot
//        }
//    }

}
