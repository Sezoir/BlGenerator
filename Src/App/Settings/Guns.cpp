#include "Guns.h"

// Qt Libs
#include <QDir>
#include <QDebug>

namespace App::Settings {

    Guns::Guns(QObject *parent, QString t_Dir)
        : QObject(parent),
          m_Dir(t_Dir + "/Guns/")
    {
        // Checks for weapon directory, if not create it
        if(!QDir(m_Dir).exists())
            QDir().mkdir(m_Dir);

        // Read json settings from all json files in directory and store them
        readSettings();

//        for(auto i : manufacturers())
//        {
//            qDebug() << i.toMap()["effect"].toString();
//        }

    }

    QVariantMap Guns::settings()
    {
        return m_settings;
    }

    QVariantMap Guns::elements()
    {
        // Return copy of elements map
        return m_settings["Elements"].toMap();
    }

    QVariantMap Guns::manufacturers()
    {
        // Return copy of manufacturers map
        return m_settings["Manufacturers"].toMap();
    }

    QVariantMap Guns::types()
    {
        // Return copy of types map
        return m_settings["Types"].toMap();
    }

    bool Guns::setManufacturers(QVariantMap & t_map)
    {
        m_settings["Manufacturers"].toMap() = t_map;

        return true;
    }


    // @todo Might change to set values, so that is can create the files if not there.
    //       If so, probably use a macro.
    void Guns::readSettings()
    {
        // Create JsonFile to read files
        Services::JsonFile fileJson;

        // Create directory of folder
        QDir dir(m_Dir);

        // Filter directory for files only
        dir.setFilter(QDir::Files);
        dir.setNameFilters(QStringList("*.json"));

        // Load all files in directory and store in m_settings
        for(auto file : dir.entryInfoList())
        {
            QString name = file.fileName().split(".")[0];

            if(!fileJson.load(m_Dir + file.fileName()))
                qDebug() << "Error when loading file.";
            m_settings.insert(name, fileJson.get().toVariantMap());
        }

    }

}

