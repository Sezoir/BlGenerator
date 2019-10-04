#pragma once

// Qt libs
#include <QString>
#include <QVector>
#include <QVariantMap>
#include <QVariantList>

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
        Weapon(BaseObject::Type type, QString rarity, QString rarityColor, int lvl)
            : BaseObject(type, rarity, rarityColor, lvl)
        {

        }

        QVariantMap elementToMap()
        {
            // Declare base map
            QVariantMap base;

            // Iterate through each element
            for(auto element : m_elements)
            {
                base.insert(element.getElement(), element.toMap());
            }

            // Return filled map
            return base;

        }

        QVariantList effectsToList()
        {
            // Declare base list
            QVariantList base;

            // Iterate through each effect
            for(auto effect : m_effects)
            {
                if(!m_effects.endsWith(effect))
                    base.push_back(effect + "\n");
                else
                    base.push_back(effect);
            }

            // Return filled list
            return base;
        }

        // List of properties of object
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
