#include "BaseFactory.h"

// Qt libs
#include <QVariantList>
#include <QDebug>
#include <QRegularExpression>

// Some base structs
#include "../Properties.h"

namespace App::Generation::Weapon {

    BaseFactory::BaseFactory(Settings::Settings & settings,
                             Services::RandContainer & random)
        : m_settings(settings)
        , m_random(random)
    {

    }

    void BaseFactory::updateBase(Services::RandContainer::Distributions generalDistribution)
    {
        // Update the distribution to be used for random numbers
        m_generalDistribution = generalDistribution;

        // Update the max number
        m_max = m_random.max<int>(m_generalDistribution);

        // Update general settings
        m_generalSettings = m_settings.general()->general();

        // Update rarities rarities
        m_rarities.clear();
        foreach(const QString & rarity, m_generalSettings["random"].toMap()["rarity"].toMap()["weapon"].toMap().keys())
        {
            m_rarities.append(rarity);
        }
    }

    int BaseFactory::roll()
    {
        return m_random.get<int>(m_generalDistribution);
    }

    QVariantMap::const_iterator BaseFactory::getSegment(const QVariantMap &list, int segment, int roll)
    {
        QVariantMap::const_iterator it = list.begin();

        if(list.isEmpty())
            return it;

        for(int i = 0; i < m_max; i+=segment)
        {
            if(roll >= i && roll <= (i+segment))
                return it;
            it++;
        }

        qDebug("Error with getSegment iterator");
        return it;
    }

    QVariantList::const_iterator BaseFactory::getSegment(const QVariantList & list, int segment, int roll)
    {
        // Create iterator
        QVariantList::const_iterator it = list.begin();

        // Test for only 1 object in list
        if(segment == m_max || list.isEmpty())
            return it;

        // Keep iterating to find segment
        for(int i = 0; i < m_max; i+=segment)
        {
            if(roll >= i && roll <= (i+segment))
                return it;
            it++;
        }

        if(it == list.end())
        {
            qDebug() << "Error with iterator" << "\nValues are " << list << segment << roll;
            exit(-1);
        }

        // Return it
        return it;
    }

    void BaseFactory::add(std::shared_ptr<Weapon> weapon, QVariantMap key)
    {
        QVariantMap::iterator it;

        for(it = key.begin(); it != key.end(); it++)
        {
            addProperty(weapon, it.key(), it.value());
        }
    }

    void BaseFactory::addProperty(std::shared_ptr<Weapon> weapon, QString key, QVariant value)
    {
        if(key == "meleeDamage")
        {
            // Check if variant is null
            if(!value.isNull())
            {
                // Check for type of data
                switch(value.userType())
                {
                case QMetaType::QString:
                {
                    // Check for Xd dice which means to multiplier
                    QRegularExpression re("\\A^(\\d+[d])$\\z", QRegularExpression::CaseInsensitiveOption);
                    if(re.match(value.toString()).hasMatch())
                    {
                        // Get the base damage of the type which it scales by
                        QString baseDamage;
                        if(weapon->m_weaponFocus == "gun")
                            baseDamage = m_settings.guns()->settings()["Types"].toMap()[weapon->m_weaponType].toMap()["meleeDamage"].toString();
                        else if(weapon->m_weaponFocus == "melee")
                            baseDamage = m_settings.melee()->settings()["Types"].toMap()[weapon->m_weaponType].toMap()["meleeDamage"].toString();
                        // Split up strings so we can get the numbers by themselves
                        QStringList baseDmgSplit = baseDamage.split("d");
                        QStringList valueSplit = value.toString().split("d");
                        // Scale the base damage based on the value
                        baseDmgSplit[0] = QString::number(baseDmgSplit[0].toInt()*valueSplit[0].toInt());
                        // Join split string back up
                        QString damage = baseDmgSplit.join("d");
                        // Add to the weapon damage
                        weapon->m_meleeDamage += damage;
                    }
                    else
                        weapon->m_meleeDamage += value.toString();
                }
                    break;
                case QMetaType::Double:
                    weapon->m_meleeDamage += value.toInt();
                    break;
                default:
                    qDebug() << "Error: Invalid meleeDamage type variable";
                    break;
                }
            }
        }
        if(key == "meleeHit")
        {
            // Check for format of effect of json, and then add to weapon qvector m_effects accordingly
            switch(value.userType())
            {
            case QMetaType::Double:
                weapon->m_meleeHit += value.toInt();
                break;
            default:
                qDebug() << "Error: Invalid type for meleeHit variable";
                break;
            }
        }
        if(key == "rangedDamage")
        {
            // Check if variant is null
            if(!value.isNull())
            {
                // Check for type of data
                switch(value.userType())
                {
                case QMetaType::QString:
                {
                    // Check for Xd dice which means to multiplier
                    QRegularExpression re("\\A^(\\d+[d])$\\z", QRegularExpression::CaseInsensitiveOption);
                    if(re.match(value.toString()).hasMatch())
                    {
                        // Get the base damage of the type which it scales by
                        QString baseDamage;
                        if(weapon->m_weaponFocus == "gun")
                            baseDamage = m_settings.guns()->settings()["Types"].toMap()[weapon->m_weaponType].toMap()["rangedDamage"].toString();
                        else if(weapon->m_weaponFocus == "melee")
                            baseDamage = m_settings.melee()->settings()["Types"].toMap()[weapon->m_weaponType].toMap()["rangedDamage"].toString();
                        // Split up strings so we can get the numbers by themselves
                        QStringList baseDmgSplit = baseDamage.split("d");
                        QStringList valueSplit = value.toString().split("d");
                        // Scale the base damage based on the value
                        baseDmgSplit[0] = QString::number(baseDmgSplit[0].toInt()*valueSplit[0].toInt());
                        // Join split string back up
                        QString damage = baseDmgSplit.join("d");
                        // Add to the weapon damage
                        weapon->m_rangedDamage += damage;
                    }
                    else
                        weapon->m_rangedDamage += value.toString();
                }
                    break;
                case QMetaType::Double:
                    weapon->m_rangedDamage += value.toInt();
                    break;
                default:
                    qDebug() << "Error: Invalid rangedDamage type variable";
                    break;
                }
            }
        }
        if(key == "rangedHit")
        {
            // Check for format of effect of json, and then add to weapon qvector m_effects accordingly
            switch(value.userType())
            {
            case QMetaType::Double:
                weapon->m_rangeHit += value.toInt();
                break;
            default:
                qDebug() << "Error: Invalid type for rangeHit variable";
                break;
            }
        }
        if(key == "range")
        {
            // Check for format of effect of json, and then add to weapon qvector m_effects accordingly
            switch(value.userType())
            {
            case QMetaType::Double:
                weapon->m_range += value.toInt();
                break;
            default:
                qDebug() << "Error: Invalid type for range variable";
                break;
            }
        }
        if(key == "effect")
        {
            // Check if variant is null
            if(!value.isNull())
            {
                // Check for format of effect of json, and then add to weapon qvector m_effects accordingly
                switch(value.userType())
                {
                case QMetaType::QString:
                    // Check for an empty list
                    if(value.toString().isEmpty())
                        return;
                    weapon->m_effects.append(value.toString());
                    break;
                case QMetaType::QVariantList:
                    // Check for an empty list
                    if(value.toList().empty())
                        return;
                    foreach(const QVariant & v, value.toList())
                        weapon->m_effects.append(v.toString());
                    break;
                default:
                    qDebug() << "Error: Invalid type for effect variable";
                    break;
                }
            }
        }
        if(key == "ammo")
        {
            // Check for format of effect of json, and then add to weapon qvector m_effects accordingly
            switch(value.userType())
            {
            case QMetaType::Double:
                weapon->m_ammo += value.toInt();
                break;
            default:
                qDebug() << "Error: Invalid type for ammo variable";
                break;
            }
        }
        if(key == "elementDamage")
        {
            // Check format of the type of the element we want to increase
            switch(value.toMap()["type"].userType())
            {
            case QMetaType::QString:
                if(value.toMap()["type"].toString() == "all")
                {
                    QVector<Element>::iterator it;
                    for(it = weapon->m_elements.begin(); it != weapon->m_elements.end(); it++)
                    {
                        // Check for format of effect of json, and then add to weapon qvector m_effects accordingly
                        switch(value.toMap()["damage"].userType())
                        {
                        case QMetaType::QString:
                        {
                            // Check for Xd dice which means to multiplier
                            QRegularExpression re("\\A^(\\d+[d])$\\z", QRegularExpression::CaseInsensitiveOption);
                            if(re.match(value.toMap()["damage"].toString()).hasMatch())
                            {
                                // Get the base damage of the type which it scales by
                                QString baseDamage;
                                if(weapon->m_weaponFocus == "gun")
                                    baseDamage = m_settings.guns()->settings()["Elements"].toMap()[it->getElement()].toMap()["elementBaseDamage"].toString();
                                else if(weapon->m_weaponFocus == "melee")
                                    baseDamage = m_settings.melee()->settings()["Elements"].toMap()[it->getElement()].toMap()["elementBaseDamage"].toString();
                                // Split up strings so we can get the numbers by themselves
                                QStringList baseDmgSplit = baseDamage.split("d");
                                QStringList valueSplit = value.toMap()["damage"].toString().split("d");
                                // Scale the base damage based on the value
                                baseDmgSplit[0] = QString::number(baseDmgSplit[0].toInt()*valueSplit[0].toInt());
                                // Join split string back up
                                QString damage = baseDmgSplit.join("d");
                                // Add to the weapon damage
                                 it->addDamage(damage);
                            }
                            else
                                // Add damage to element
                                it->addDamage(value.toMap()["damage"].toString());
                        }
                            break;
                        case QMetaType::Double:
                            // Add damage to element
                            it->addDamage(value.toMap()["damage"].toInt());
                            break;
                        default:
                            qDebug() << "Error: Invalid type for elementDamage variable";
                            break;
                        }
                    }
                }
                else
                {
                    QVector<Element>::iterator it;
                    for(it = weapon->m_elements.begin(); it != weapon->m_elements.end(); it++)
                        if(it->getElement() == value.toMap()["type"].toString())
                        {
                            switch(value.toMap()["damage"].userType())
                            {
                            case QMetaType::QString:
                            {
                                // Check for Xd dice which means to multiplier
                                QRegularExpression re("\\A^(\\d+[d])$\\z", QRegularExpression::CaseInsensitiveOption);
                                if(re.match(value.toMap()["damage"].toString()).hasMatch())
                                {
                                    // Get the base damage of the type which it scales by
                                    QString baseDamage;
                                    if(weapon->m_weaponFocus == "gun")
                                        baseDamage = m_settings.guns()->settings()["Elements"].toMap()[it->getElement()].toMap()["elementBaseDamage"].toString();
                                    else if(weapon->m_weaponFocus == "melee")
                                        baseDamage = m_settings.melee()->settings()["Elements"].toMap()[it->getElement()].toMap()["elementBaseDamage"].toString();
                                    // Split up strings so we can get the numbers by themselves
                                    QStringList baseDmgSplit = baseDamage.split("d");
                                    QStringList valueSplit = value.toMap()["damage"].toString().split("d");
                                    // Scale the base damage based on the value
                                    baseDmgSplit[0] = QString::number(baseDmgSplit[0].toInt()*valueSplit[0].toInt());
                                    // Join split string back up
                                    QString damage = baseDmgSplit.join("d");
                                    // Add to the weapon damage
                                     it->addDamage(damage);
                                }
                                else
                                    // Add damage to element
                                    it->addDamage(value.toMap()["damage"].toString());
                            }
                                break;
                            case QMetaType::Double:
                                // Add damage to element
                                it->addDamage(value.toMap()["damage"].toInt());
                                break;
                            default:
                                qDebug() << "Error: Invalid type for elementDamage variable";
                                break;
                            }
                        }
                }
                break;
            }
        }
        if(key == "elementChance")
        {
            // Iterate through each element
            QVector<Element>::iterator it;
            for(it = weapon->m_elements.begin(); it != weapon->m_elements.end(); it++)
            {
                // Check for format of effect of json, and then add to weapon qvector m_effects accordingly
                switch(value.userType())
                {
                case QMetaType::Double:
                    // Add chance value to element
                    it->addChance(value.toInt());
                    break;
                default:
                    qDebug() << "Error: Invalid type for elementChance variable";
                    break;
                }
            }
        }

    }
}
