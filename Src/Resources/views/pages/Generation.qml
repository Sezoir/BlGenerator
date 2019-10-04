import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQml.Models 2.12
import Fluid.Controls 1.0 as FluidControls

import Object 1.0
import "../templates"

Item {
    id: root
    width: parent.width
    height: parent.height
    anchors.fill: parent

    property int fontSize: 18
    property string fontFamily: ""

    FluidControls.Sidebar {
        property bool expand: true
        id: sidebar
        expanded: expand
        z:2
        width: 300
        autoFlick: false

        ColumnLayout {
            id: layout
            anchors.fill: parent

            ToolBar {
                id: toolHeader

                Layout.preferredWidth: parent.width
                Layout.preferredHeight: 40
                Layout.fillHeight: false

                background: Rectangle {
                    anchors.fill: toolHeader
                    color: "White"
                }

                RowLayout {
                    anchors.fill: parent
                    ToolButton {
                        id: toggle
                        implicitWidth: 40
                        implicitHeight: 40
                        onClicked: sidebar.toggleExpand()
                        contentItem: FluidControls.Icon {
                            source: FluidControls.Utils.iconUrl("navigation/chevron_left")
                            size: toggle.implicitHeight
                        }
                    }
                    FluidControls.SubheadingLabel {
                        text: "PROPERTIES"
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        Layout.rightMargin: 35
                        Layout.fillWidth: true
                    }
                }
            }

            Item {
                Layout.preferredWidth: parent.width
                Layout.minimumHeight: 40
                Layout.fillHeight: true

                Flickable {
                    id: flickable
                    anchors.fill: parent
                    anchors.rightMargin: 20
                    contentHeight: grid.implicitHeight
                    contentWidth: grid.implicitWidth
                    flickableDirection: Flickable.VerticalFlick
                    boundsBehavior: Flickable.DragOverBounds

                    ScrollBar.vertical: ScrollBar {
                        id: scrollBar
                        parent: flickable.parent
                        anchors {
                            top: flickable.top
                            bottom: flickable.bottom
                            right: flickable.right
                        }
                    }

                    GridLayout {
                        id: grid
                        columns: 1
                        width: sidebar.width-20

                        RowLayout {
                            Layout.alignment: Qt.AlignHCenter
                            SpinBox {
                                from: 1
                                to: 30
                                editable: true
                                onValueModified: {GenerateController.quantity = value}
                            }
                            FluidControls.BodyLabel {
                                text: "Quantity"
                            }
                        }
                        RowLayout {
                            Layout.alignment: Qt.AlignHCenter
                            SpinBox {
                                from: 1
                                to: 30
                                editable: true
                                onValueModified: {GenerateController.level = value}
                            }
                            FluidControls.BodyLabel {
                                text: "Level"
                            }
                        }
                        RowLayout {
                            Layout.alignment: Qt.AlignHCenter
                            ComboBox {
                                height: 40
                                currentIndex: 0
                                model: ["All",
                                        "Weapons",
                                        "Shields",
                                        "Grenades",
                                        "Class Mods"]
                                }
                            FluidControls.BodyLabel {
                                text: "Type"
                            }
                        }
                        RowLayout {
                            Layout.alignment: Qt.AlignHCenter
                            ComboBox {
                                height: 40
                                Layout.preferredWidth: 200
                                currentIndex: 0
                                model: GenerateController.rarities
                                onActivated: {GenerateController.rarity = currentText}
                                }
                            FluidControls.BodyLabel {
                                text: "Rarity"
                            }
                        }
                    }
                }
            }

            ToolButton {
                id: generate
                text: "Generate"
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: 40
                Layout.fillHeight: false
                onClicked: GenerateController.clicked()
            }
        }

        function toggleExpand()
        {
            if(expand == true)
            {
                //expandSidebar.visible = true;
                expand = !expand;
            }
            else
            {
                //expandSidebar.visible = false;
                expand = !expand;
            }
        }
    }

    ToolButton {
        id: expandSidebar
        z:1
        implicitHeight: 40
        implicitWidth: 40
        visible: !sidebar.expand
        anchors {
            top: parent.top
            left: parent.left
        }
        onClicked: sidebar.toggleExpand()
        contentItem: FluidControls.Icon {
            size: expandSidebar.implicitHeight
            source: FluidControls.Utils.iconUrl("navigation/chevron_right")
        }
    }

    Rectangle {
        id: rectangle
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: sidebar.right
        }

        //anchors.fill: parent
        anchors.margins: 35
        color: "lightblue"
        //radius: 35
        border.width: 5
        border.color: "steelblue"
        //clip: true


        GridView {
            id: gridPackages
            property int packageHeight: 320
            property int packageWidth: 250
            clip: true
            anchors.fill: parent
            anchors.margins: 20

            cellHeight: packageHeight + 40
            cellWidth: packageWidth + 40

            flickableDirection: Flickable.VerticalFlick

            ScrollBar.vertical: ScrollBar {
//                parent: middle.parent
//                anchors.top: middle.top
//                anchors.right: middle.right
//                anchors.bottom: middle.bottom
            }

            model: ObjectModel {
                list: objectList
            }

//            delegate: Text {
//                text: model.type + "\n" + model.rarity + "\n" + model.level
//            }

            delegate: Component {
                Loader {
                    property string _name: model.name
                    property int _playerNum: model.playerNum
                    property int _level: model.level
                    property string _rarity: model.rarity
                    property color _rarityColor: model.rarityColor
                    property string _manufacturer: model.manufacturer

                    property string _weaponType: model.weaponType
                    property string _weaponFocus: model.weaponFocus
                    property string _rangedDamage: model.rangedDamage
                    property string _meleeDamage: model.meleeDamage
                    property string _rangedHit: model.rangedHit
                    property string _meleeHit: model.meleeHit
                    property string _range: model.range
                    property string _ammo: model.ammo
                    property var _elements: model.elements
                    property var _effects: model.effects

                    /*
            WeaponTypeRole,
            WeaponFocusRole,
            RangedDamageRole,
            MeleeDamageRole,
            RangedHitRole,
            MeleeHitRole,
            RangeRole,
            ManufacturerRole,
            ElementsRole,
            EffectsRole,
            AmmoRole
                      */

                    width: gridPackages.packageWidth
                    height: gridPackages.packageHeight
                    source: switch(model.type) {
                            case "Weapon": return "../templates/PackageWeapon.qml"
                            }
                }

            }
        }

    }

}

