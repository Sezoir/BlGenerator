#pragma once

// Qt libs
#include <QObject>
#include <QQmlApplicationEngine>
#include <QString>

// Std libs
#include <memory>

// Base Class
#include "Controller.h"

// Loot Generation Class
#include "../Generation/Generator.h"

// Base object class
#include "../Generation/BaseObject.h"

// Weapon object
#include "../Generation/Weapon/Object.h"

namespace App::View {
        class Generate : public QObject, public Controller
        {
            Q_OBJECT
            Q_PROPERTY(QString loot READ loot NOTIFY lootChanged)

        public:
            /**
             * @brief Generate constructor
             * @param t_parent: QObject parent
             * @param t_generator: Reference to generator class
             */
            Generate(QObject * t_parent, Generation::Generator & t_generator);

            /**
             * @brief Generate destructor
             */
            ~Generate() {}

            // @todo Everything below to be changed/improved once loot generation is more complete
            QString loot() const {return m_loot;}
            void setLoot(const QString &);

        signals:
            void lootChanged();

        public slots:
            void clicked();

        private:
            QString m_loot;
            Generation::Generator & m_generator;

            int counter;
        };
    }
