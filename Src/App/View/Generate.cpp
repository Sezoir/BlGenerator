#include "Generate.h"

// Qt libs
#include <QDebug>
#include <QQuickItem>
#include <QQmlContext>

// Object properties
#include "../Generation/Properties.h"

namespace App::View {

        Generate::Generate(QObject * parent,
                           QQmlApplicationEngine * engine,
                           Generation::Generator & generator,
                           Settings::Settings & settings)
            : QObject(parent)
            , m_engine(engine)
            , m_generator(generator)
            , m_settings(settings)
            , m_objectModel(new Models::ObjectModel(parent))
            , m_objectList(new Models::ObjectList(parent))//m_objectModel->list())
            , m_rarity("All")
            , m_level(1)
            , m_loot("Hello World!")
        {
            counter = 0;

            // Test object list
//            Generation::BaseObject test(Generation::BaseObject::Type::Weapon, "legendary", 30);
//            m_objectList->addItem(test);

            registerModels();
            setContextObjects();
            makeConnections();
        }

        QStringList Generate::rarities()
        {
            // Define qstringlist for use
            QStringList rarities;

            // Add in default all entry
            rarities.append("All");

            // Iterate through each type and then its rarities then add each unique rarity to list
            foreach(const QVariant & objType, m_settings.general()->general()["random"].toMap()["rarity"].toMap())
            {
                foreach(const QString & rarity, objType.toMap().keys())
                {
                    if(!rarities.contains(rarity, Qt::CaseInsensitive))
                        rarities.append(rarity);
                }
            }

            // Return copy of list
            return rarities;
        }

        QString Generate::rarity() const
        {
            return m_rarity;
        }

        void Generate::setRarity(QString rarity)
        {
            qDebug() << "Rarity has been changed to" << rarity;
            m_rarity = rarity;
        }

        int Generate::level()
        {
            return m_level;
        }

        void Generate::setLevel(int level)
        {
            m_level = level;
        }

        void Generate::registerModels()
        {
            qmlRegisterType<Models::ObjectModel>("Object", 1, 0, "ObjectModel");
            qmlRegisterUncreatableType<Models::ObjectList>("Object", 1, 0, "ObjectList",
                                                           QStringLiteral("ObjectList should not be created in QML"));
        }

        void Generate::setContextObjects()
        {
            m_engine->rootContext()->setContextProperty(QStringLiteral("objectList"), m_objectList);
        }

        void Generate::clicked()
        {
//            Generation::BaseObject test(Generation::BaseObject::Type::Weapon, "legendary", 30);
//            Generation::BaseObject test;
//            test.m_lvl = 30;
//            test.m_rarity = "rarity";
            std::shared_ptr<Generation::BaseObject> test = m_generator.create(m_level);

            m_objectList->addItem(test);
//            for(int i = 0; i < 1; i++)
//            {
//            qDebug() << QString("Clicked!") << counter;
//            counter++;
//            std::shared_ptr<Generation::BaseObject> objBase = m_generator.create(1);
//            std::shared_ptr<Generation::Weapon::Weapon> obj = std::shared_ptr<Generation::Weapon::Weapon>(std::static_pointer_cast<Generation::Weapon::Weapon>(objBase));
//            QString objString = "";
//            objString.append("Name: " + obj->m_name + "\n");
//            objString.append("WeaponType: " + obj->m_weaponType + "\n");
//            objString.append("Type: " + obj->m_type + "\n");
//            objString.append("Rarity: " + obj->m_rarity + "\n");
//            objString.append("Manufacturer: " + obj->m_manufacturer + "\n");
//            objString.append("Ammo: " + QString::number(obj->m_ammo) + "\n");
//            objString.append("Range: " + QString::number(obj->m_range) + "\n");
//            objString.append("Melee Hit: " + QString::number(obj->m_meleeHit) + "\n");
//            objString.append("Ranged Hit: " + QString::number(obj->m_rangeHit) + "\n");
//            objString.append("Level: " + QString::number(obj->m_lvl) + "\n");
//            objString.append("Melee Damage: " + obj->m_meleeDamage.toString() + "\n");
//            objString.append("Ranged Damage: " + obj->m_rangedDamage.toString() + "\n");
//            objString.append("Elements: \n");
//            foreach(Generation::Element v, obj->m_elements)
//                objString.append(v.toString());
//            objString.append("Effects: \n");
//            foreach(const QString & v, obj->m_effects)
//                objString.append(v + "\n");
//            setLoot(objString);
//            }
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
