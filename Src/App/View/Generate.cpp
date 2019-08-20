#include "Generate.h"

#include <QDebug>
#include <QQuickItem>
#include "../Generation/Properties.h"

namespace App::View {

        Generate::Generate(QObject * t_parent, Generation::Generator & t_generator)
            : QObject(t_parent)
            , m_loot("Hello World!")
            , m_generator(t_generator)
        {
            counter = 0;
            makeConnections();
        }

        void Generate::clicked()
        {
            for(int i = 0; i < 1; i++)
            {
            qDebug() << QString("Clicked!") << counter;
            counter++;
            std::shared_ptr<Generation::BaseObject> objBase = m_generator.create();
            std::shared_ptr<Generation::Weapon::Weapon> obj = std::shared_ptr<Generation::Weapon::Weapon>(std::static_pointer_cast<Generation::Weapon::Weapon>(objBase));
            QString objString = "";
            objString.append("Name: " + obj->m_name + "\n");
            objString.append("WeaponType: " + obj->m_weaponType + "\n");
            objString.append("Type: " + obj->m_type + "\n");
            objString.append("Rarity: " + obj->m_rarity + "\n");
            objString.append("Manufacturer: " + obj->m_manufacturer + "\n");
            objString.append("Ammo: " + QString::number(obj->m_ammo) + "\n");
            objString.append("Range: " + QString::number(obj->m_range) + "\n");
            objString.append("Melee Hit: " + QString::number(obj->m_meleeHit) + "\n");
            objString.append("Ranged Hit: " + QString::number(obj->m_rangeHit) + "\n");
            objString.append("Level: " + QString::number(obj->m_lvl) + "\n");
            objString.append("Melee Damage: " + obj->m_meleeDamage.toString() + "\n");
            objString.append("Ranged Damage: " + obj->m_rangedDamage.toString() + "\n");
            objString.append("Elements: \n");
            foreach(Generation::Element v, obj->m_elements)
                objString.append(v.toString());
            objString.append("Effects: \n");
            foreach(const QString & v, obj->m_effects)
                objString.append(v + "\n");
            setLoot(objString);
            }
        }

        void Generate::setLoot(const QString & value)
        {
            if(value == m_loot)
            {
                return;
            }

            m_loot = value;
            emit lootChanged();
        }

    }
