#pragma once

// Qt libs
#include <QObject>
#include <QMap>
#include <QString>
#include <QVariantMap>

// Std Libs
#include <memory>

// Base factory
#include "BaseFactory.h"

// Weapon struct
#include "Object.h"

namespace App::Generation::Weapon {
    class MeleeFactory : public QObject, public BaseFactory
    {
        Q_OBJECT
    public:
        /**
         * @brief MeleeFactory constructor
         * @param parent: QObject parent
         * @param settings: Reference to settings class
         * @param random: Reference to random class
         */
        explicit MeleeFactory(QObject *parent,
                              Settings::Settings & settings,
                              Services::RandContainer & random);

        /**
         * @brief Updates variables for this class and BaseFactory
         * @param generalDistribution
         */
        void update(Services::RandContainer::Distributions generalDistribution);

        /**
         * @brief Randomly create a melee weapon
         * @param weapon: Shared pointer reference to current weapon
         * @return
         */
        std::shared_ptr<Weapon> createMelee(std::shared_ptr<Weapon> weapon);

    private:
        // Melee settings qvariantmap
        QVariantMap m_meleeSettings;

        /**
         * @todo Redescribe function to sound clearer
         * @brief For each file name, it will update the m_segments to "rough" ints equal to the segments of the max of the
         *        distribution/number of objects each file
         */
        void segmentate();

        // @todo Might change names to some map to allow new types of weapons to be created in future
        // Struct to store equally seperated value of segments for each file
        struct segments
        {
            int meleeManufacturers;
            QMap<QString, int> meleeManufacturerPrefix;
            QMap<QString, int> meleeElementsPrefix;
            QMap<QString, int> meleeElements;
            QMap<QString, int> meleeElementsChance;
            QMap<QString, int> partsManufacturer;
            QMap<QString, int> rarityEffects;
            QMap<QString, int> typeNames;
            int parts;
            int meleeTypes;
        };

        // Variable of the struct segments
        segments m_segments;

        /**
         * @brief Sets base parameters for a random melee weapon
         * @param weapon: Reference to current weapon
         */
        void setTemplate(std::shared_ptr<Weapon> & weapon);

        /**
         * @brief Rolls for manfacturer and add manufacturer stats onto weapon
         * @param weapon: Reference to current weapon
         */
        void addManufacturer(std::shared_ptr<Weapon> & weapon);

        /**
         * @brief Rolls for element and add element stats to weapon
         * @param weapon: Reference to current weapon
         */
        void addElements(std::shared_ptr<Weapon> & weapon);

        /**
         * @brief Rolls for parts and add the part stats to weapon
         * @param weapon: Reference to current weapon
         */
        void addParts(std::shared_ptr<Weapon> & weapon);

        /**
         * @brief Add 1 part to the weapon struct
         * @param weapon: Reference to current weapon
         * @param part: QString of the name of the part in Parts.json
         */
        void addPart(std::shared_ptr<Weapon> & weapon, QString part);

        /**
         * @brief Adds the correct number of effects dependig on the weapon
         * @param weapon: Reference to current weapon
         */
        void addRarityEffects(std::shared_ptr<Weapon> & weapon);

        /**
         * @brief Scales the weapon type properties based on the level
         * @param weapon: Reference to current weapon
         */
        void scaleWeapon(std::shared_ptr<Weapon> & weapon);

        /**
         * @brief Scales the weapon elements properties based on the level
         * @param weapon: Reference to current weapon
         */
        void scaleElements(std::shared_ptr<Weapon> & weapon);

    };
}

