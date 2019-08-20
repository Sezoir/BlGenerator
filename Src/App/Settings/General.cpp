#include "General.h"

// Qt Libs
#include <QDir>
#include <QDebug>

namespace App::Settings {

    General::General(QObject *parent, QString t_Dir)
        : QObject(parent)
        , m_Dir(t_Dir)
    {
        // Checks for weapon directory, if not create it
        if(!QDir(m_Dir).exists())
            QDir().mkdir(m_Dir);

        // Read json settings from all json files in directory and store them
        readSettings();

//        for(auto i : general())
//        {
//            qDebug() << i.toMap().first().toString();
        //        }
    }

    QVariantMap General::settings()
    {
        return m_settings;
    }

    QVariantMap General::general()
    {
        return m_settings["General"].toMap();
    }

    bool General::setGeneral(QVariantMap &t_map)
    {
        m_settings["General"].toMap() = t_map;

        return true;
    }

    void General::readSettings()
    {
        // Create JsonFile to read files
        Services::JsonFile fileJson;

        // Create directory of folder
        QDir dir(m_Dir);

        // Load file in dir and store in m_settings
        if(!fileJson.load(m_Dir + "General.json"))
        {
            qDebug() << "Error when loading file.";
            return;
        }

        m_settings.insert("General", fileJson.get().toVariantMap());
    }




}
