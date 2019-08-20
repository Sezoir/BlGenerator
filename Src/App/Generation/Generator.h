#pragma once

// Qt Libs
#include <QObject>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QVariantMap>
#include <QVariant>
#include <QMap>
#include <QPair>

// Std Libs
#include <memory>

// Settings class
#include "../Settings/Settings.h"

// Random number generator
#include "../Services/RandContainer.h"

// Base Object
#include "BaseObject.h"

// Weapon factory
#include "Weapon/Factory.h"

// Weapon object
#include "Weapon/Object.h"

namespace App::Generation {
        class Generator : public QObject
        {
            Q_OBJECT
        public:
            /**
             * @brief Generator constructor
             * @param parent
             * @param t_settings
             */
            explicit Generator(QObject *parent, Settings::Settings & settings);

            /**
             * @brief Generator destructor
             */
            ~Generator() = default;

            void update();

            /**
             * @brief Create a random loot
             * @return
             */
            std::shared_ptr<BaseObject> create();

        signals:

        public slots:

        private:

            // Settings class
            Settings::Settings & m_settings;

            // Random number generator class
            Services::RandContainer & m_random;

            // Random distributions
            Services::RandContainer::Distributions m_generalDistribution;
            Services::RandContainer::Distributions m_rarityDistribution;

            // Object collection
            // @todo Might change to a unique pointer and move or just provide a reference to it
            QVector<std::shared_ptr<BaseObject>> m_objects;

            // Weapon factory
            Weapon::Factory & m_weaponFactory;


            // Values that correspond to "sections" of the loot distribution when pulling out a random number
            struct Objects
            {
                int weapon;
                int shield;
                int grenade;
                int classMod;
            };

            // @todo may change to integers and *100 on the value for memory efficiency
            // Store rarity values
            //QMap<QString, QMap<QString, double>> m_rarityChance;
            QMap<QString, QVector<QPair<QString, double>>> m_rarityChance;

            // Store object chances
            Objects m_objectsChance;

            /**
             * @brief Reads a distribution, stores is enum variable, and creates it in m_random
             * @param distribution: QVariant of the distribution
             */
            void createDistribution(QVariant & distribution, QString name, QString use);

            /**
             * @brief Checks a string for a corresponding distribution and returns the distribution
             * @param distribution: String of the distribution name
             * @return Services::RandContainer::Distributions value corresponding to the string
             */
            void setDistribution(QVariant & distributions);

            /**
             * @brief Gets a random rarity string based on the type
             * @param type: type of object you want a rarity from
             * @return QString value of the rarity value
             */
            QString getRarity(QString type);





        };
    }
