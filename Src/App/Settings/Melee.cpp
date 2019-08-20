#include "Melee.h"

// Qt Libs
#include <QDir>
#include <QDebug>

namespace App::Settings {

    Melee::Melee(QObject *parent, QString t_Dir)
        : QObject(parent)
        , m_Dir(t_Dir + "/Melee/")
    {
        // Checks for weapon directory, if not create it
        if(!QDir(m_Dir).exists())
            QDir().mkdir(m_Dir);

        // Register file names
        m_fileNames.append("Parts.json");
        m_fileNames.append("Elements.json");
        m_fileNames.append("Manufacturers.json");
        m_fileNames.append("Types.json");
        m_fileNames.append("Rarity.json");
        m_fileNames.append("Scaling.json");
        m_fileNames.append("ElementsScaling.json");

        // Read json settings from all json files in directory and store them
        readSettings();
    }

    QVariantMap Melee::settings()
    {
        return m_settings;
    }

    QVariantMap Melee::parts()
    {
        return m_settings["Parts"].toMap();
    }

    QVariantMap Melee::elements()
    {
        return m_settings["Elements"].toMap();
    }

    QVariantMap Melee::manufacturers()
    {
        return m_settings["Manufacturers"].toMap();
    }

    QVariantMap Melee::types()
    {
        return m_settings["Types"].toMap();
    }


    void Melee::readSettings()
    {
        // Create JsonFile to read files
        Services::JsonFile fileJson;

        // Create directory of folder
        QDir dir(m_Dir);

        // Load file in dir and store in m_settings
        foreach(const QString & v, m_fileNames)
        {
            if(!fileJson.load(m_Dir + v))
            {
                qDebug() << "Error when loading file.";
                return;
            }
            m_settings.insert(v.split(".")[0], fileJson.get().toVariantMap());
        }
    }




}
