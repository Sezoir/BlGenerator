#include "Factory.h"

// Qt libs
#include <QDebug>

// Std libs
#include <cmath>

namespace App::Generation::Weapon
{
    Factory::Factory( QObject *parent
                      , App::Settings::Settings & settings
                      , Services::RandContainer & random)
        : QObject (parent)
        , m_settings(settings)
        , m_random(random)
        , m_melee(*new MeleeFactory(parent, settings, random))
        , m_gun(*new GunFactory(parent, settings, random))
    {

    }

    Factory::~Factory()
    {

    }

    void Factory::update(Services::RandContainer::Distributions generalDistribution)
    {
        // Update the distribution to be used for random numbers
        m_generalDistribution = generalDistribution;

        // Update melee factory
        m_melee.update(generalDistribution);

        // Update gun factory
        m_gun.update(generalDistribution);

        // Update the max number
        m_max = m_random.max<int>(m_generalDistribution);

        // Update general settings
        m_generalSettings = m_settings.general()->settings();

        // Update the segmentation values for each file
        segmentate();
    }

    std::shared_ptr<Weapon> Factory::create(int lvl, QString rarity, QString rarityColor)
    {
        // Create default weapon template struct to be filled
        auto weapon = std::make_shared<Weapon>(BaseObject::Type::Weapon, rarity, rarityColor, lvl);

//        // Determine weapon type
//            // Roll for a sword or gun
//            int myRoll = roll();
//            // If sword then update the weapon
//            // Otherwise roll again and then check
//            if (myRoll >= m_weaponSegmentation.gun && myRoll <= m_weaponSegmentation.sword)
//            {
//                weapon = createSword(weapon);
//            }
//            else if(myRoll >= 0 && myRoll < m_weaponSegmentation.gun)
//            {
//                myRoll = roll();
//                QVariantMap::const_iterator gunType = getSegment(m_settings.weapons()->rangedTypes(), m_segmentation.gunTypes, myRoll);
//                weapon->m_weaponType = gunType.key();
//            }

        //weapon = m_melee.createMelee(weapon);
        weapon = m_gun.createGun(weapon);

        return weapon;
    }



    void Factory::segmentate()
    {
        // Work out the unequal segmentation for the weapon type
        double weight = m_generalSettings["random"].toMap()["weapon"].toMap()["gun"].toDouble();
        m_weaponSegmentation.gun = static_cast<int>(std::round(static_cast<double>(m_max)*weight));

        // @todo Change to be more general, i.e melee
        // Let sword have the remainder
        weight = m_generalSettings["random"].toMap()["weapon"].toMap()["sword"].toDouble();
        m_weaponSegmentation.sword = static_cast<int>(std::round(static_cast<double>(m_max)*weight));
    }





}
