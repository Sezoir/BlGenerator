#include "Settings.h"

// Qt Libs
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <QGuiApplication>

namespace App::Settings {
        Settings::Settings(QObject * parent)
            : QObject(parent)
        {
            loadSettings();
        }

        QSharedPointer<Guns> Settings::guns()
        {
            return m_guns;
        }

        QSharedPointer<General> Settings::general()
        {
            return m_general;
        }

        QSharedPointer<Melee> Settings::melee()
        {
            return m_melee;
        }

        void Settings::loadSettings()
        {
            // Get dir of program config
            QString pathDir = getDir();

            // Create the setting
                // Weapons
                m_guns = QSharedPointer<Guns>(new Guns(this, pathDir));
                m_general = QSharedPointer<General>(new General(this, pathDir));
                m_melee = QSharedPointer<Melee>(new Melee(this, pathDir));
        }

        QString Settings::getDir()
        {
            // Get path to config folder
            QString path = QDir().currentPath() + "/Config/";

            // Check path exists, if not create it
            if(!QDir(path).exists())
                QDir().mkdir(path);

            // Return path
            return path;
        }


    }
