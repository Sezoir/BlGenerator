import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtGraphicalEffects 1.0
import Fluid.Controls 1.0 as FluidControls

import "../templates"

Item {
    property string name: parent._name

    id: root
    //anchors.fill: parent
    height: parent.height
    width: parent.width
    x: 0
    y: 0

    PackageTemplate {
        packageName: name
        //anchors.fill: parent
        height: parent.height
        width: parent.width
        x: 0
        y: 0
    }
}
