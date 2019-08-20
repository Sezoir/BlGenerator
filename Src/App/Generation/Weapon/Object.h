#pragma once

// Qt libs
#include <QString>
#include <QVector>

// Std libs
#include <memory>

// General universal structs for properties
#include "../Properties.h"

// Base Object
#include "../BaseObject.h"

namespace App::Generation::Weapon
{
    // Base Weapon struct
    // @todo may change name to object for readability
    struct Weapon : public BaseObject
    {
        Weapon(QString type, QString rarity, int lvl)
            : BaseObject(type, rarity, lvl)
        {

        }
        QString m_name;
        QString m_weaponType;
        QString m_weaponFocus;
        Damage m_rangedDamage = Damage(Roll::create("0d0"), 0, Ability("Error"));
        Damage m_meleeDamage = Damage(Roll::create("0d0"), 0, Ability("Error"));
        int m_rangeHit = 0;
        int m_meleeHit = 0;
        int m_range = 0;
        QString m_manufacturer;
        QVector<Element> m_elements;
        QVector<QString> m_effects;
        int m_ammo = 0;
    };
}
