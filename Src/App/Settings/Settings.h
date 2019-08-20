#pragma once

// Qt Libs
#include <QObject>
#include <QQmlApplicationEngine>
#include <QString>
#include <QSharedPointer>
#include <QMap>

// Setting Packages
#include "Guns.h"
#include "General.h"
#include "Melee.h"

namespace App::Settings {
        class Settings : public QObject
        {
            Q_OBJECT
        public:
            // Constructor
            explicit Settings(QObject *);

            // Destructor
            ~Settings() = default;

            // Get functions (Returns qvariant)
            QSharedPointer<Guns> guns();
            QSharedPointer<General> general();
            QSharedPointer<Melee> melee();

        private:
            // Storing json tree as qvariantmap
            QSharedPointer<Guns> m_guns;
            QSharedPointer<General> m_general;
            QSharedPointer<Melee> m_melee;

            // Loads all the settings files
            void loadSettings();

            // Gets the current directory of the exe
            QString getDir();
        };
    }

