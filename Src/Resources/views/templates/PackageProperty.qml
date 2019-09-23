import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import Fluid.Controls 1.0 as FluidControls

Item {
    // Changable properties
    property string key: "Error"
    property string value: "NoValue"
    property string hint: "Error"
    property bool hintEnabled : false
    property int textSize: 18

    // Internal properties
    QtObject {
        id: internal
        property bool showHint: (hintEnabled && mouseArea.containsMouse)
    }

    id: root
    Layout.minimumWidth: textSize
    height: 20
    Layout.alignment: Qt.AlignCenter

    Rectangle {
        id: background
        z: -1
        anchors.fill: parent
        color: "#31353a"
        opacity: 0.8
    }

    //@todo need to implement based on idea of states (InMouse or OutMouse)
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: hintEnabled
        z: 3
        propagateComposedEvents: true
    }

    RowLayout {
        anchors.fill: parent
        FluidControls.SubheadingLabel {
            Layout.preferredHeight: parent.height
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft
            Layout.leftMargin: 10
            text: key
            //font.pixelSize: textSize
            verticalAlignment: Text.AlignVCenter

        }

        FluidControls.SubheadingLabel {
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: contentWidth
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 10
            text: value
            //font.pixelSize: textSize
            verticalAlignment: Text.AlignVCenter
            level: 2
        }
    }

    ToolTip {
        x: mouseArea.mouseX + 20
        y: mouseArea.mouseY + 20
        z: 3
        text: qsTr(hint)
        visible: internal.showHint
    }
}
