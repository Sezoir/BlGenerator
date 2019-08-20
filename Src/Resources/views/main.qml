import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.3

ApplicationWindow  {
    visible: true
    width: 640
    height: 480
    title: qsTr("Bl Generator")

    Material.theme: Material.Light
    Material.accent: Material.Purple

    Column {
        x: 20
        y: 20
        id: col
        Button {
            id: generateButton
            text: qsTr("Press Me!")
            onPressed: GenerateController.clicked()
        }
        Text {
            id: someText
            text: GenerateController.loot
        }
    }

}
