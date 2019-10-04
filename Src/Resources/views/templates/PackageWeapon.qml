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
    property int playerNum: parent._playerNum
    property int level: parent._level
    property string rarity: parent._rarity
    property color rarityColor: parent._rarityColor
    property string manufacturer: parent._manufacturer

    property string weaponType: parent._weaponType
    property string weaponFocus: parent._weaponFocus
    property string rangedDamage: parent._rangedDamage
    property string meleeDamage: parent._meleeDamage
    property string rangedHit: parent._rangedHit
    property string meleeHit: parent._meleeHit
    property string range: parent._range
    property string ammo: parent._ammo
    property var elements: parent._elements
    property var effects: parent._effects

    id: root
    height: parent.height
    width: parent.width
    x: 0
    y: 0

    PackageTemplate {
        id: template
        packageName: parent.name
        playerNum: parent.playerNum
        level: parent.level
        rarity: parent.rarity
        rarityColor: parent.rarityColor
        manufacturer: parent.manufacturer

        height: parent.height
        width: parent.width
        x: 0
        y: 0

        PackageProperty {
            id: propRangedDamage
            Layout.preferredWidth: template.contentWidth
            key: "Ranged Damage"
            value: rangedDamage
        }
        PackageProperty {
            id: propMeleeDamage
            Layout.preferredWidth: template.contentWidth
            key: "Melee Damage"
            value: meleeDamage
        }
        PackageElementProperty {
            id: propElements
            Layout.preferredWidth: template.contentWidth
            elements: root.elements
        }

        PackageProperty {
            id: propRangedHit
            Layout.preferredWidth: template.contentWidth
            key: "Ranged Hit"
            value: rangedHit
        }
        PackageProperty {
            id: propMeleeHit
            Layout.preferredWidth: template.contentWidth
            key: "Melee Hit"
            value: meleeHit
        }
        PackageProperty {
            id: propRange
            Layout.preferredWidth: template.contentWidth
            key: "Range"
            value: range
        }
        PackageProperty {
            id: propAmmo
            Layout.preferredWidth: template.contentWidth
            key: "Ammo"
            value: ammo
        }
    }
}
