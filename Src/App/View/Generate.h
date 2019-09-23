#pragma once

// Qt libs
#include <QObject>
#include <QQmlApplicationEngine>
#include <QString>
#include <QStringList>

// Std libs
#include <memory>

// Settings class
#include "../Settings/Settings.h"

// Base Class
#include "Controller.h"

// Loot Generation Class
#include "../Generation/Generator.h"

// Base object class
#include "../Generation/BaseObject.h"

// Weapon object
#include "../Generation/Weapon/Object.h"

// Custom models
#include "../Models/ObjectModel.h"

// Custom models list
#include "../Models/ObjectList.h"

namespace App::View {
        class Generate : public QObject, public Controller
        {
            Q_OBJECT
            Q_PROPERTY(QString loot READ loot NOTIFY lootChanged)
            Q_PROPERTY(QStringList rarities READ rarities NOTIFY raritiesChanged)
            Q_PROPERTY(QString rarity READ rarity WRITE setRarity)
            Q_PROPERTY(int level READ level WRITE setLevel)

        public:
            /**
             * @brief Generate constructor
             * @param t_parent: QObject parent
             * @param t_generator: Reference to generator class
             */
            Generate(QObject * parent,
                     QQmlApplicationEngine * engine,
                     Generation::Generator & generator,
                     Settings::Settings & settings);

            /**
             * @brief Generate destructor
             */
            ~Generate() {}

            /**
             * @brief Returns a QStringList of all rarity types
             */
            QStringList rarities();

            /**
             * @brief Returns qstring of current rarity
             * @return
             */
            QString rarity() const;

            /**
             * @brief Sets the current rarity of object to be made
             */
            void setRarity(QString rarity);

            /**
             * @brief Returns a int of current level
             * @return
             */
            int level();

            /**
             * @brief Sets the current level of the object to be made
             * @param level
             */
            void setLevel(int level);

            // @todo Everything below to be changed/improved once loot generation is more complete
            QString loot() const {return m_loot;}
            void setLoot(const QString &);

        signals:
            void raritiesChanged();
            void lootChanged();

        public slots:
            void clicked();

        private:
            // Application engine
            QQmlApplicationEngine * m_engine;

            // Object generator
            Generation::Generator & m_generator;

            // Settings class
            Settings::Settings & m_settings;

            // Custom model for objects
            Models::ObjectModel * m_objectModel;

            // Custom model list for objects
            Models::ObjectList * m_objectList;

            // List of all rarities
            QStringList m_rarities;

            // String of the current rarity to use
            QString m_rarity;

            // Integer of current level to use
            int m_level;

            /**
             * @brief Register the models used in this view
             */
            void registerModels();

            /**
             * @brief Set the context objects related to generate view
             */
            void setContextObjects();

            QString m_loot;
            int counter;
        };
    }
