#pragma once

// Qt libs
#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QMap>
#include <QString>
#include <QVariantList>

// Std libs
#include <memory>

// Weapon struct object
#include "Object.h"

// Settings class
#include "../../Settings/Settings.h"

// Random class
#include "../../Services/RandContainer.h"

// Melee factory
#include "MeleeFactory.h"

// Gun factory
#include "GunFactory.h"

namespace App::Generation::Weapon {
    class Factory : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief Factory constructor
         * @param parent: QObject parent
         * @param settings: Reference to Settings class
         * @param random: Reference to RandContainer class
         */
        explicit Factory( QObject *parent
                        , Settings::Settings & settings
                        , Services::RandContainer & random);

        /**
         * @brief Factory destructor
         */
        ~Factory();

        /**
         * @brief Updates the variables of the factory
         * @param generalDistribution: Integer based distribution enum from RandContainer
         */
        void update(Services::RandContainer::Distributions generalDistribution);

        /**
         * @brief Create a shared pointer to a weapon struct
         * @param lvl: Level of the weapon
         * @param rarity: Rarity of the weapon
         * @return Shared pointer to the weapon struct
         */
        std::shared_ptr<Weapon> create(int lvl, QString rarity);

    private:
        // Settings class
        Settings::Settings & m_settings;

        // General settings qvariantmap
        QVariantMap m_generalSettings;

        // Random number generator
        Services::RandContainer & m_random;

        // Store reference to distribution to use in this class
        Services::RandContainer::Distributions m_generalDistribution;

        // Melee factory
        MeleeFactory & m_melee;

        // Gun factory
        GunFactory & m_gun;

        // Max number of distribution
        int m_max = 100;

        /**
         * @todo Redescribe function to sound clearer
         * @brief For each file name, it will update the m_segmentation to "rough" ints equal to the segmentation of the max of the
         *        distribution/number of objects each file
         */
        void segmentate();

        // Struct to store unequal seperated value of segementation for weapon types
        struct weaponSegmentation
        {
            int gun;
            int sword;
        };

        // Variable of the struct weaponSegmentation
        weaponSegmentation m_weaponSegmentation;


    };

}
