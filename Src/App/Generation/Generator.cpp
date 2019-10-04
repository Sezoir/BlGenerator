#include "Generator.h"

// Std libs
#include <cmath>
#include <utility>

namespace App::Generation {
    Generator::Generator(QObject *parent, Settings::Settings & settings)
        : QObject(parent)
        , m_settings(settings)
        , m_random(*new Services::RandContainer)
        , m_weaponFactory(*new Weapon::Factory(parent, settings, m_random))
    {
        update();
    }

    void Generator::update()
    {
        // Set distribution values, and then create distributions
        setDistribution(m_settings.general()->general()["random"].toMap()["distributions"]);

        // Set rarity values from settings in m_rarityChance map based on object type
        foreach(const QString & type, m_settings.general()->general()["random"].toMap()["rarity"].toMap().keys())
        {
            foreach(const QString & rarity, m_settings.general()->general()["random"].toMap()["rarity"].toMap()[type].toMap().keys())
            {
                m_rarityChance[type]
                        .append(qMakePair<QString, double>
                                (rarity,
                                 m_settings.general()->general()["random"].toMap()["rarity"].toMap()[type].toMap()[rarity].toDouble()));
            }
        }

        // Order m_rarityChance map for for ascending value doubles
        // Note i use the bubble sort here
        foreach(const QString & type, m_rarityChance.keys())
        {
            int size = m_rarityChance[type].size() - 1;
            for(int i = 0; i < size-1; i++)
            {
                for(int j = 0; j < size-i; j++)
                {
                    if(m_rarityChance[type][j].second > m_rarityChance[type][j+1].second)
                    {
                        m_rarityChance[type].move(j, j+1);
                    }
                }
            }

        }

        // Set object chance values in m_objectsChance struct
        m_objectsChance.weapon = static_cast<int>(std::round(m_random.max<double>(m_generalDistribution)*m_settings.general()->general()["random"].toMap()["objects"].toMap()["weapon"].toDouble()));
        m_objectsChance.shield = static_cast<int>(std::round(m_random.max<double>(m_generalDistribution)*m_settings.general()->general()["random"].toMap()["objects"].toMap()["shield"].toDouble()));
        m_objectsChance.grenade = static_cast<int>(std::round(m_random.max<double>(m_generalDistribution)*m_settings.general()->general()["random"].toMap()["objects"].toMap()["grenade"].toDouble()));
        m_objectsChance.classMod = static_cast<int>(std::round(m_random.max<double>(m_generalDistribution)*m_settings.general()->general()["random"].toMap()["objects"].toMap()["classMod"].toDouble()));

        // Update each factory
        m_weaponFactory.update(m_generalDistribution);

    }

    std::shared_ptr<BaseObject> Generator::create(int level)
    {
        // Determine the type of object
        int objChance = m_random.get<int>(m_generalDistribution);
        //int level = 30;

        //m_objects.push_back(m_weaponFactory.create(level, rarity));

//        if(objChance >= 0 && objChance < m_objectsChance.weapon)
//            return "Weapon";
//        if(objChance >= m_objectsChance.weapon && objChance < m_objectsChance.shield)
//            return "Shield";
//        if(objChance >= m_objectsChance.shield && objChance < m_objectsChance.grenade)
//            return "Grenade";
//        if(objChance >= m_objectsChance.grenade && objChance <= m_objectsChance.classMod)
//            return "Class Mod";

//        if(objChance >= 0 && objChance < m_objectsChance.weapon)
//            m_objects.push_back(m_weaponFactory.create(level));
//        if(objChance >= m_objectsChance.weapon && objChance < m_objectsChance.shield)
//            m_objects.push_back(m_shieldFactory.create(level));
//        if(objChance >= m_objectsChance.shield && objChance < m_objectsChance.grenade)
//            m_objects.push_back(m_grenadeFactory.create(level));
//        if(objChance >= m_objectsChance.grenade && objChance < m_objectsChance.classMod)
//            m_objects.push_back(m_classModFactory.create(level));

        // Determine rarity of object
        QString rarity = getRarity("weapon");
        // Get associated rarity color
        QString rarityColor = m_settings.general()->general()["rarity"].toMap()[rarity].toMap()["color"].toString();

        auto weapon = m_weaponFactory.create(level, rarity, rarityColor);

        return std::move(weapon);
    }

    void Generator::createDistribution(QVariant & distribution, QString name, QString use)
    {
        // Check for valid distribution
        // Then store acording to appropiate enum variable
        // Then create it from m_random
        if(name == "UniformInt")
        {
            if(use == "generalDistribution")
                m_generalDistribution = Services::RandContainer::Distributions::UniformInt;
            if(use == "rarityDistribution")
                m_rarityDistribution = Services::RandContainer::Distributions::UniformInt;
            m_random.create(Services::RandContainer::Distributions::UniformInt,
                            distribution.toMap().value("min").toInt(),
                            distribution.toMap().value("max").toInt());
            return;
        }
        if(name == "ExponentialDouble")
        {
            if(use == "generalDistribution")
                m_generalDistribution = Services::RandContainer::Distributions::ExponentialDouble;
            if(use == "rarityDistribution")
                m_rarityDistribution = Services::RandContainer::Distributions::ExponentialDouble;
            m_random.create(Services::RandContainer::Distributions::ExponentialDouble,
                            distribution.toMap().value("param").toDouble());
            return;
        }

        qDebug() << "Error: distribution doesnt exist: " << name;

    }

    void Generator::setDistribution(QVariant & distributions)
    {
        QVariantMap::iterator i;
        auto distro = distributions.toMap();

        for(i = distro.begin(); i != distro.end(); ++i)
        {
            if(i.value().toMap()["general"].toBool() == true)
            {
                createDistribution(i.value(), i.key(), "generalDistribution");
            }
            if(i.value().toMap()["rarity"].toBool() == true)
            {
                createDistribution(i.value(), i.key(), "rarityDistribution");
            }
        }
    }

    QString Generator::getRarity(QString type)
    {
        double chance = m_random.get<double>(m_rarityDistribution);

        for(int i = 0; i < m_rarityChance[type].size()-1; i++)
        {
            if(chance > 0 && chance <= m_rarityChance[type][0].second)
                return m_rarityChance[type][0].first;
            else if(chance > m_rarityChance[type][i].second && chance <= m_rarityChance[type][i+1].second)
                return m_rarityChance[type][i].first;
            else if(chance > m_rarityChance[type].last().second)
                return m_rarityChance[type].last().first;
        }

        return QString("Error");
    }

}
