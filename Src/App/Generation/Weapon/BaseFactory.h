#pragma once

// Qt libs
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

namespace App::Generation::Weapon {
    /**
     * @brief A base factory that provides the gun and melee factory some common useful functions
     */
    class BaseFactory
    {
    public:
        /**
         * @brief BaseFactory constructor
         * @param random
         * @param generalDistribution
         */
        explicit BaseFactory(Settings::Settings & settings,
                             Services::RandContainer & random);

        /**
         *
         */
        void updateBase(Services::RandContainer::Distributions generalDistribution);

        // Facade to getting a random integer
        int roll();

        // Returns a iterator representing the position of a qvariant map corresponding to the its segment.
        QVariantMap::const_iterator getSegment(const QVariantMap & list, int segment, int roll);

        QVariantList::const_iterator getSegment(const QVariantList & list, int segment, int roll);

        // General function that goes through every stat and just adds it
        void add(std::shared_ptr<Weapon> weapon, QVariantMap key);

        // General function to add stats onto weapon struct
        void addProperty(std::shared_ptr<Weapon> weapon, QString key, QVariant value);

    protected:
        // Settings class
        Settings::Settings & m_settings;

        // General qvariantmap settings
        QVariantMap m_generalSettings;

        // Random number generator
        Services::RandContainer & m_random;

        // Store reference to distribution to use in this class
        Services::RandContainer::Distributions m_generalDistribution;

        // Max number of random number generator
        int m_max;

        // All rarity types for weapons
        QVector<QString> m_rarities;

    };
}

