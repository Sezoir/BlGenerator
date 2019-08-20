#include "GunFactory.h"

// Qt Libs
#include <QVariantList>
#include <QList>
#include <QVector>

namespace App::Generation::Weapon {

    GunFactory::GunFactory(QObject *parent,
                           Settings::Settings &settings,
                           Services::RandContainer &random)
        : QObject(parent)
        , BaseFactory (settings, random)
    {

    }

    void GunFactory::update(Services::RandContainer::Distributions generalDistribution)
    {
        // Update base factory
        updateBase(generalDistribution);

        // Update gun settings
        m_gunSettings = m_settings.guns()->settings();

        // Calculate segments
        segmentate();
    }

    std::shared_ptr<Weapon> GunFactory::createGun(std::shared_ptr<Weapon> weapon)
    {
        // Roll for random gun type and base stats associated with it
        setTemplate(weapon);

        // Roll for manufacturer and stats associated with it
        addManufacturer(weapon);

        // Roll for element and stats associated with it
        addElements(weapon);

        // Add parts
        addParts(weapon);

        // Add rarity effects
        addRarityEffects(weapon);

        // Scale weapon to its level
        scaleWeapon(weapon);

        // Scale weapons elements to its level
        scaleElements(weapon);

        return weapon;
    }

    void GunFactory::segmentate()
    {
        // Define max and min
        int max;
        int min;

        // Gun manufacturers
        max = m_gunSettings["Manufacturers"].toMap().count();
        // Check for error
        if(max == 0)
        {
            qDebug() << "Error with manufacturers" << max;
            exit(-1);
        }
        m_segments.manufacturers = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));

        // Gun types
        max = m_gunSettings["Types"].toMap().count();
        // Check for error
        if(max == 0)
        {
            qDebug() << "Error with types" << max;
            exit(-1);
        }
        m_segments.types = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));

        // Gun Parts
        max = m_gunSettings["Parts"].toMap().count();
        // Check for error
        if(max == 0)
        {
            qDebug() << "Error with names" << max;
            exit(-1);
        }
        m_segments.parts = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));

        // Type names
        foreach(const QString & key, m_gunSettings["Types"].toMap().keys())
        {
            max = m_gunSettings["Types"].toMap()[key].toMap()["names"].toList().count();
            // Check for error
            if(max < 0 || max > m_max)
            {
                qDebug() << "Error with Gun type names segments" << max;
                exit(-1);
            }
            if(max != 0)
                m_segments.typeNames[key] = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));
            else
                m_segments.typeNames[key] = m_max;
        }

        // Gun manufacturer name prefixs
        foreach(const QString & key, m_gunSettings["Manufacturers"].toMap().keys())
        {
            max = m_gunSettings["Manufacturers"].toMap()[key].toMap()["prefix"].toList().count();
            // Check for error
            if(max < 0 || max > m_max)
            {
                qDebug() << "Error with Gun manufacturer segments" << max;
                exit(-1);
            }
            m_segments.manufacturerPrefix[key] = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));
        }

        // Gun elements
        foreach(const QString & key, m_gunSettings["Manufacturers"].toMap().keys())
        {
            max = m_gunSettings["Manufacturers"].toMap()[key].toMap()["elements"].toList().count();
            // Check for error
            if(max < 0 || max > m_max)
            {
                qDebug() << "Error with Gun elements segments" << max;
                exit(-1);
            }
            if(max != 0)
                m_segments.elements[key] = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));
            else
                m_segments.elements[key] = m_max;
        }

        // Gun element prefixs
        foreach(const QString & key, m_gunSettings["Elements"].toMap().keys())
        {
            max = m_gunSettings["Elements"].toMap()[key].toMap()["prefix"].toList().count();
            // Check for error
            if(max < 0 || max > m_max)
            {
                qDebug() << "Error with Gun elements prefix segments" << max;
                exit(-1);
            }
            if(max != 0)
                m_segments.elementsPrefix[key] = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));
            else
                m_segments.elementsPrefix[key] = m_max;
        }

        // Gun element chance
        foreach(const QString & key, m_gunSettings["Elements"].toMap().keys())
        {
            max = m_gunSettings["Elements"].toMap()[key].toMap()["chanceMax"].toInt();
            min = m_gunSettings["Elements"].toMap()[key].toMap()["chanceMin"].toInt();

            // Check for error
            if(max < min || max > m_max)
            {
                qDebug() << "Error with Gun elements chance prefix segments" << max;
                exit(-1);
            }
            // Check max and min for being the same
            if(max == min)
                m_segments.elementsChance[key] = m_max;
            // Check for max to be non-zero as we know max > min
            else if(max != 0)
                m_segments.elementsChance[key] = static_cast<int>(std::round(static_cast<double>(m_max)/
                                                                                  (static_cast<double>(max) - static_cast<double>(min) ) ));
            // Else set to zero for testing later
            else
                m_segments.elementsPrefix[key] = 0;
        }

        // Gun parts
        foreach(const QString & key, m_gunSettings["Parts"].toMap().keys())
        {
            // Get max count of parts
            max = m_gunSettings["Parts"].toMap()[key].toMap().count();
            // Check for error
            if(max < 0 || max > m_max)
            {
                qDebug() << "Error with Gun parts segments" << max;
                exit(-1);
            }
            if(max != 0)
                m_segments.partsManufacturer[key] = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));
            else
                m_segments.partsManufacturer[key] = m_max;
        }

        // Rarity effects
        foreach(const QString & key, m_gunSettings["Rarity"].toMap().keys())
        {
            // Get max count of parts
            max = m_gunSettings["Rarity"].toMap()[key].toMap()["effects"].toList().count();
            // Check for error
            if(max < 0 || max > m_max)
            {
                qDebug() << "Error with rarity effects segments" << max;
                exit(-1);
            }
            if(max != 0)
                m_segments.rarityEffects[key] = static_cast<int>(std::round(static_cast<double>(m_max)/static_cast<double>(max)));
            else
                m_segments.rarityEffects[key] = m_max;
        }

    }

    void GunFactory::setTemplate(std::shared_ptr<Weapon> &weapon)
    {
        // Determine gun type
            // Get random number
            int myRoll = roll();
            // Get copy of qvariantmap of types
            const QVariantMap & types = m_gunSettings["Types"].toMap();
            // Get an iterator pointing the corresponding value to the random number
            QVariantMap::const_iterator typeIt = getSegment(types, m_segments.types, myRoll);
            // Check for a error
            if(typeIt == types.end())
            {
                qDebug() << "Error with gun type iterator" << "\nTry checking the Melee/Types json file for correctly named keys";
                exit(-1);
            }
            // Store value as qstring
            QString type = typeIt.key();

        // Set weapon type
        weapon->m_weaponType = type;

        // Set weapon focus
        weapon->m_weaponFocus = "gun";

        // Set ammo base
        weapon->m_ammo = m_gunSettings["Types"].toMap()[type].toMap()["ammo"].toInt();

        // Add effect
        {
        QString effect = m_gunSettings["Types"].toMap()[type].toMap()["effect"].toString();
        if(!effect.isEmpty())
            weapon->m_effects.append(effect);
        }

        {
        // Set ranged damage base
            QVariant damage = m_gunSettings["Types"].toMap()[weapon->m_weaponType].toMap()["rangedDamage"];

            switch(damage.userType())
            {
            case QMetaType::Double:
                weapon->m_rangedDamage = Damage(damage.toInt(),
                                                Ability(m_gunSettings["Types"].toMap()[weapon->m_weaponType].toMap()["attribute"].toString()));
                break;
            case QMetaType::QString:
                weapon->m_rangedDamage = Damage(damage.toString(),
                                                Ability(m_gunSettings["Types"].toMap()[weapon->m_weaponType].toMap()["attribute"].toString()));
                break;
            default:
                qDebug() << "Error ranged damage base of incorrect type";
            }
        }

        // Set melee damage base
        weapon->m_meleeDamage = Damage("0d0+0",
                                       Ability(m_gunSettings["Types"].toMap()[weapon->m_weaponType].toMap()["attribute"].toString()));

        // Set range base
        weapon->m_range = m_gunSettings["Types"].toMap()["range"].toInt();

        // Set melee hit base
        weapon->m_meleeHit = m_gunSettings["Types"].toMap()["meleeHit"].toInt();

        // Set range hit base
        weapon->m_rangeHit = m_gunSettings["Types"].toMap()["rangeHit"].toInt();

        // Create name base
        // Get random number
        myRoll = roll();
        // Get copy of names qlist
        const QVariantList & names = m_gunSettings["Types"].toMap()[type].toMap()["names"].toList();
        // Get an iterator pointing the corresponding value to the random number
        QVariantList::const_iterator name = getSegment(names, m_segments.typeNames[type], myRoll);
        // Check for a error
        if(typeIt == types.end())
        {
            qDebug() << "Error with melee type iterator" << "\nTry checking the Melee/Types json file for correctly named keys";
            exit(-1);
        }
        // Set field to iterator value
        weapon->m_name = name->toString();
    }

    void GunFactory::addManufacturer(std::shared_ptr<Weapon> &weapon)
    {
        // Determine manufacturer
            // Get random number
            int myRoll = roll();
            // Get copy of manufacturer qvariantmap
            const QVariantMap & manufacturers = m_gunSettings["Manufacturers"].toMap();
            // Get an iterator pointing the corresponding value to the random number
            QVariantMap::const_iterator manufacturer = getSegment(manufacturers, m_segments.manufacturers, myRoll);
            // Check for a error
            if(manufacturer == manufacturers.end())
            {
                qDebug() << "Error with melee manufacturers iterator" << "\nTry checking the Melee/Manufacturers json file for correctly named keys";
                exit(-1);
            }
            // Set field to iterator key
            weapon->m_manufacturer = manufacturer.key();

            // Add on manufacturer stats
            add(weapon, manufacturer->toMap());

        // Add on manufactuer name prefix
            // Get random number
            myRoll = roll();
            // Get copy of names qlist
            const QVariantList & manufacturerPrefixs = m_gunSettings["Manufacturers"].toMap()[weapon->m_manufacturer].toMap()["prefix"].toList();
            // Get an iterator pointing the corresponding value to the random number
            QVariantList::const_iterator manufacturerPrefix = getSegment(manufacturerPrefixs, m_segments.manufacturerPrefix[weapon->m_manufacturer], myRoll);
            // Check for a error
            if(manufacturerPrefix == manufacturerPrefixs.end())
            {
                qDebug() << "Error with melee manufacturer prefix iterator" << "\nTry checking the Melee/Manufacturers json file for correctly named keys";
                exit(-1);
            }
            // Add prefix to the name string
            weapon->m_name.insert(0, manufacturerPrefix->toString() + " ");
    }

    void GunFactory::addElements(std::shared_ptr<Weapon> &weapon)
    {
        // Declare number of elements on weapon
        int elementCount;
        // Check for existance of numberElements key
        if(m_gunSettings["Manufacturers"].toMap()[weapon->m_manufacturer].toMap().contains("numberElements"))
            elementCount = m_gunSettings["Manufacturers"].toMap()[weapon->m_manufacturer].toMap()["numberElements"].toInt();
        else
            elementCount = 0;

        // Declare qvector of element names to test for duplciate elements
        QVector<QString> values;
        // Add elements already on weapon
        foreach(const Element & v, weapon->m_elements)
            values.append(v.m_element);

        for(int i = 0; i < elementCount; i++)
        {
        // Add on element
            // Get random number
            int myRoll = roll();
            // Get copy of qlist of elements for current manufacturer (not reference due to removing from list)
            const QVariantList & elements = m_gunSettings["Manufacturers"].toMap()[weapon->m_manufacturer].toMap()["elements"].toList();
            // Check that the number of elements is less or equal to than elementCount
            if(elementCount > elements.count())
            {
                qDebug() << "Error number of elements wanted for manufacturer" << weapon->m_manufacturer
                         << "exceeds number of elements manufacturer can have";
                exit(-1);
            }
            // Get a element first
            QVariantList::const_iterator element = getSegment(elements, m_segments.elements[weapon->m_manufacturer], myRoll);
            // Then keep gettings rolls if the element is already on the weapon
            while(values.contains(element->toString()))
            {
                // Reroll number
                myRoll = roll();
                // Get an iteration pointing to the corresponding value to the random number
                element = getSegment(elements, m_segments.elements[weapon->m_manufacturer], myRoll);
            }
            // Check for a error
            if(elements.isEmpty());
            else if(element == elements.end())
            {
                qDebug() << "Error with element type iterator" << "\nTry checking the Melee/Manufacturers json file for correctly named keys";
                exit(-1);
            }
            else
            {
                // Add value to vector of elements on weapon
                values.append(element->toString());

                // Get a random number for the chance of the element
                int chance;
                    // Check for segment to be zero
                    if(m_segments.elementsChance[element->toString()] == 0)
                        chance = 0;
                    // Check for min and max to be the same
                    else if(m_segments.elementsChance[weapon->m_manufacturer] == m_max)
                        chance = m_gunSettings["Elements"].toMap()[element->toString()].toMap()["chanceMax"].toInt();
                    else
                    {
                        // Get random number
                        myRoll = roll();
                        // Get segment split
                        int segment = m_segments.elementsChance[element->toString()];
                        // Get some number to iterate by
                        int i = 0;
                        // Keep checking for roll to be in segment, if not increase iterator by one
                        while(!(myRoll >= i*segment && myRoll <= ((i+1)*segment)))
                        {
                            i += 1;
                        }
                        // Chance will then equal iterator + min
                        chance = i+m_gunSettings["Elements"].toMap()[element->toString()].toMap()["chanceMin"].toInt();
                    }

                // Create element under conditions
                auto el = Element(  Damage(m_gunSettings["Elements"].toMap()[element->toString()].toMap()["elementBaseDamage"].toString(),
                                                           Ability(Ability::Abilities::Elements)),
                                    element->toString(),
                                    m_gunSettings["Elements"].toMap()[element->toString()].toMap()["elementEffect"].toList(),
                                    m_gunSettings["Elements"].toMap()[element->toString()].toMap()["condition"].toString(),
                                    chance
                                 );

                // Add to weapon vector
                weapon->m_elements.append(el);
                // Add element stats onto weapon
                add(weapon, m_gunSettings["Elements"].toMap()[element->toString()].toMap());

            }

        // Add on element prefix
            // Get random number
            myRoll = roll();
            // Get copy of element prefix qlist
            const QVariantList & elementPrefixs = m_gunSettings["Elements"].toMap()[element->toString()].toMap()["prefix"].toList();
            // Get an iteration pointing to the corresponding value to the random number
            QVariantList::const_iterator elementPrefix = getSegment(elementPrefixs, m_segments.elementsPrefix[element->toString()], myRoll);
            // Check for a error
            if(elementPrefix == elementPrefixs.end());
            else
            {
                weapon->m_name.insert(0, elementPrefix->toString() + " ");
            }
        }
    }

    void GunFactory::addParts(std::shared_ptr<Weapon> &weapon)
    {
        // Go through parts
        // Go through parts
        foreach(const QVariant & i, m_gunSettings["Types"].toMap()[weapon->m_weaponType].toMap()["parts"].toList())
        {
            addPart(weapon, i.toString());
        }
    }

    void GunFactory::addPart(std::shared_ptr<Weapon> &weapon, QString part)
    {
        // Get random number
        int myRoll = roll();
        // Get a random manufacturer for the select part
        // Get copy of qvaraintmap of manufacturer parts
        const QVariantMap & manufacturers = m_gunSettings["Parts"].toMap()[part].toMap();
        // Get an iteration pointing to the corresponding value to the random number
        QVariantMap::const_iterator manufacturer = getSegment(manufacturers, m_segments.partsManufacturer[part], myRoll);
        // Check for a error
        if(manufacturer == manufacturers.end() && manufacturers.count() > 1)
        {
            qDebug() << "Error with addPart const_iterator";
            exit(-1);
        }
        else
        {
            add(weapon, manufacturers[manufacturer.key()].toMap());
        }

    }

    void GunFactory::addRarityEffects(std::shared_ptr<Weapon> & weapon)
    {
        // Declare map for storing
        QMap<QString, int> rarityEffectsList;

        // Add to the map each element from which we should add an effect with a number corresponding to the number of effect from that rarity
        foreach(const QString & rarity, m_rarities)
        {
            foreach(const QString & rarityNumb, m_gunSettings["Rarity"].toMap()[weapon->m_rarity].toMap().keys())
            {
                if(rarity == rarityNumb && m_gunSettings["Rarity"].toMap()[weapon->m_rarity].toMap()[rarityNumb].toInt() != 0)
                {
                    rarityEffectsList[rarity] = m_gunSettings["Rarity"].toMap()[weapon->m_rarity].toMap()[rarityNumb].toInt();
                }
            }
        }

        // Check for rarities with no effects
        if(rarityEffectsList.empty())
            return;

        // Add the effect to the weapon from each rarity pool
        foreach(const QString & rarity, rarityEffectsList.keys())
        {
            for(int i = 0; i < rarityEffectsList[rarity]; i++)
            {
                // Get random number
                int myRoll = roll();
                // Get a random effect from rarity
                // Get copy of qvaraintlist of effects
                const QVariantList & effects = m_gunSettings["Rarity"].toMap()[rarity].toMap()["effects"].toList();
                // Get an iteration pointing to the corresponding value to the random number
                QVariantList::const_iterator effect = getSegment(effects, m_segments.rarityEffects[rarity], myRoll);
                // Check for a error
                if(effect == effects.end() && effects.count() != 1)
                {
                    qDebug() << "Error with addPart const_iterator";
                    exit(-1);
                }
                else
                {
                    add(weapon, effect->toMap());
                }
            }
        }

    }

    void GunFactory::scaleWeapon(std::shared_ptr<Weapon> &weapon)
    {
        foreach(const QString & lvlStr, m_gunSettings["Scaling"].toMap()[weapon->m_weaponType].toMap().keys())
        {
            bool numChk;
            int lvl = lvlStr.toInt(&numChk);
            if(numChk == false)
            {
                qDebug() << "Error with Scaling json file. One of the levels is a non-integer number";
                exit(-1);
            }

            if(lvl <= weapon->m_lvl)
            {
                add(weapon, m_gunSettings["Scaling"].toMap()[weapon->m_weaponType].toMap()[lvlStr].toMap());
            }

        }
    }

    void GunFactory::scaleElements(std::shared_ptr<Weapon> &weapon)
    {
        // Create iterator of element vector
        QVector<Element>::iterator ele;
        for(ele = weapon->m_elements.begin(); ele != weapon->m_elements.end(); ele++)
        foreach(const QString & lvlStr, m_gunSettings["ElementsScaling"].toMap()[ele->getElement()].toMap().keys())
        {
            bool numChk;
            int lvl = lvlStr.toInt(&numChk);
            if(numChk == false)
            {
                qDebug() << "Error with Scaling json file. One of the levels is a non-integer number";
                exit(-1);
            }

            if(lvl <= weapon->m_lvl)
            {
                add(weapon, m_gunSettings["ElementsScaling"].toMap()[ele->getElement()].toMap()[lvlStr].toMap());
            }

        }
    }


}
