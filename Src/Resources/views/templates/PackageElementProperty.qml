import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import Fluid.Controls 1.0 as FluidControls

Item {
    // Changable properties
    property color rarityColor: "white"
    property var elements: ({})
    property color backgroundColor: "#31353a"
    property color foregroundColor: "lightblue"
    property int delegateHeight: 40

    // Hint properties
    property string hint: "Error"
    property bool hintEnabled : false

    // Internal properties
    QtObject {
        id: internal
        property bool showHint: (hintEnabled && mouseArea.containsMouse)
        property int height: delegateHeight*rootView.count + rootView.spacing*rootView.count
    }

    id: root
    height: internal.height
    //Layout.minimumHeight: header.height + contentItem.totalHeight + 3*rootColumn.spacing
    //headerList.height + contentItem.totalHeight + 3*rootColumn.spacing
    //height: headerList.height + contentItem.totalHeight + 3*rootColumn.spacing//60//list.totalHeight//20
    //Layout.alignment: Qt.AlignCenter
    clip: true

    Component.onCompleted: {


    }

    //@todo need to implement based on idea of states (InMouse or OutMouse)
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: hintEnabled
        z: 3
        propagateComposedEvents: true
    }

    ListModel {
            id: elementModel

            Component.onCompleted: {
                for(var element in elements)
                {
                    elementModel.append({"element" : element,
                                        "color" : elements[element]["color"],
                                        "damage" : elements[element]["damage"],
                                        "condition" : elements[element]["condition"],
                                        "chance" : elements[element]["chance"],
                                        "effect" : elements[element]["effect"],
                                        "iconPath" : elements[element]["iconPath"]})

                }
            }
        }

    Rectangle {
        anchors.fill: parent
        color: "blue"
        z: -5
    }

    ListView {
        id: rootView
        anchors.fill: parent

        spacing: 10

        model: elementModel

        Component.onCompleted: {
            console.log(rootView.count)
        }

        delegate: Rectangle {
            id: background
            height: delegateHeight
            width: rootView.width
            color: backgroundColor

            Row {
                anchors.fill: parent
                Column {
                    height: parent.height
                    width: 0.25*parent.width
                    FluidControls.BodyLabel {
                        id: elementType
                        height: parent.height/2
                        width: parent.width

                        text: model.element

                        style: Text.Outline
                        styleColor: "Black"
                        level: 2
                        color: model.color
                    }
                    FluidControls.Icon {
                        height: parent.height/2
                        width: parent.width
                        colorize: false
                        source: "file:///" + applicationPath + model.iconPath
                     }

                }

                ColumnLayout {
                    id: propLayout
                    height: parent.height
                    width: 0.75*parent.width

                    PackageProperty {
                        id: damage

                        key: "Damage:"
                        value: model.damage

                        Layout.leftMargin: 30
                        Layout.fillHeight: true
                        Layout.preferredWidth: propLayout.width - Layout.leftMargin

                        rarityColor: "White"
                    }
                    PackageProperty {
                        id: chance

                        key: "Chance:"
                        value: model.chance

                        Layout.leftMargin: 30
                        Layout.fillHeight: true
                        Layout.preferredWidth: propLayout.width - Layout.leftMargin

                        rarityColor: "White"
                    }

//                    FluidControls.BodyLabel {
//                        id: damage

//                        text: model.damage

//                        Layout.fillHeight: true
//                        Layout.preferredWidth: propLayout.width


//                        style: Text.Outline
//                        styleColor: "Black"
//                        level: 2
//                        color: model.color
//                    }
//                    FluidControls.BodyLabel {
//                        id: chance

//                        text: model.chance

//                        horizontalAlignment: Text.AlignRight

//                        Layout.fillHeight: true
//                        Layout.preferredWidth: propLayout.width

//                        style: Text.Outline
//                        styleColor: "Black"
//                        level: 2
//                        color: model.color
//                    }
                }
            }



            //                  FluidControls.BodyLabel {
            //                      id: chance
            //                      height: implicitHeight
            //                      width: parent.width
            //                      text: "Chance: " + model.chance
            //                      verticalAlignment: Text.AlignVCenter
            //                      horizontalAlignment: Text.AlignHCenter
            //                      style: Text.Outline
            //                      styleColor: "Black"
            //                      color: model.color
            //                      level: 2
            //                  }
        }


    }

//    Column {
//        id: rootColumn
//        anchors.fill: parent
//        anchors.margins: 5
//        spacing: 10
//        Item {
//            id: header
//            anchors {
//                left: parent.left
//                right: parent.right
//            }
//            height: 40
//            Rectangle {
//                id: headerListBackground
//                anchors.fill: parent
//                color: foregroundColor
//                z: -10
//            }
//            ListView {
//                id: headerList
//                anchors.fill: parent
//                anchors.margins: 5

//                orientation: Qt.Horizontal
//                spacing: 10

//                header: FluidControls.SubheadingLabel {
//                    height: parent.height
//                    width: implicitWidth + 15
//                    text: "Elements:"
//                    verticalAlignment: Text.AlignVCenter
//                    fontSizeMode: Text.Fit
//                    style: Text.Outline
//                    styleColor: "Black"
//                    color: rarityColor
//                }

//                model: elementModel

//                delegate: FluidControls.Icon {
//                              z: 3
//                              height: headerList.height
//                              width: height
//                              colorize: false
//                              source: "file:///" + applicationPath + model.iconPath
//                          }
//                }
//        }

//    Item {
//        id: contentItem
//        property int totalHeight: 0
//        anchors {
//            left: parent.left
//            right: parent.right
//        }
//        height: totalHeight

//        ListView {
//            id: contentList
//            anchors.fill: parent
//            //anchors.margins: 10

//            spacing: 10

//            onCountChanged: {
//                if(contentList.count == 0)
//                {
//                    contentItem.totalHeight = 30;
//                    return;
//                }

//                var newHeight = 0;
//                var curHeight = 0;
//                for(var child in contentList.contentItem.children)
//                {
//                    curHeight = contentList.contentItem.children[child].height;
//                    newHeight += contentList.contentItem.children[child].height;
//                }

//                contentItem.totalHeight = newHeight - curHeight + (contentList.count-1)*contentList.spacing;
//            }

//            model: elementModel

//            delegate: Item {
//                height: damage.height + chance.height//element.height + damage.height + condition.height + chance.height + effect.height
//                width: contentList.width

//                Rectangle {
//                    id: contentListBackground
//                    anchors.fill: parent
//                    color: foregroundColor
//                    z: -10
//                }

//                Column {
//                  id: column
//                  anchors.fill: parent
//                  FluidControls.BodyLabel {
//                      id: damage
//                      height: implicitHeight
//                      width: parent.width
//                      text: "Damage: " + model.damage
//                      verticalAlignment: Text.AlignVCenter
//                      horizontalAlignment: Text.AlignHCenter
//                      style: Text.Outline
//                      styleColor: "Black"
//                      color: model.color
//                      level: 2
//                  }
//                  FluidControls.BodyLabel {
//                      id: chance
//                      height: implicitHeight
//                      width: parent.width
//                      text: "Chance: " + model.chance
//                      verticalAlignment: Text.AlignVCenter
//                      horizontalAlignment: Text.AlignHCenter
//                      style: Text.Outline
//                      styleColor: "Black"
//                      color: model.color
//                      level: 2
//                  }
//                }
//            }
//          }

//        }
//    }

    ToolTip {
        x: mouseArea.mouseX + 20
        y: mouseArea.mouseY + 20
        z: 3
        text: qsTr(hint)
        visible: internal.showHint
    }
}












