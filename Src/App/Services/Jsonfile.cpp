#include "Jsonfile.h"

// Qt Libs
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

namespace App::Services {
    JsonFile::JsonFile() : m_path("")
    {

    }

    bool JsonFile::load(QString t_path)
    {
        // Set temp path
        setPath(t_path);

        // Load the file
        QFile loadFile(t_path);

        // Open the file and check if failed
        if(!loadFile.open(QFile::ReadOnly))
        {
            // @todo create better logging of errors.
            qDebug() << "Error loading file at " << t_path;

            return false;
        }

        // Get file data
        QByteArray saveData = loadFile.readAll();

        // Close file
        loadFile.close();

        // Load the document in json stored format
        QJsonParseError err;

        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &err));

        // Check for correct format of json
        if(err.error != 0)
            qDebug() << "Json document not correctly formated: " << err.errorString();

        // Get the object
        m_json = loadDoc.object();

        return true;
    }

    bool JsonFile::update(QJsonObject t_json)
    {
        // Update stored json value
        m_json = t_json;

        // Load the file
        QFile saveFile(m_path);

        // Open the fire and error if failed
        if(!saveFile.open(QFile::WriteOnly))
        {
            // @todo create better logging of error
            qDebug() << "Error loading file at " << m_path;

            return false;
        }

        // Create a json format document
        QJsonDocument saveDoc(m_json);

        // Save the file in the correct format
        saveFile.write(saveDoc.toJson(QJsonDocument::Indented));

        return true;
    }

    QJsonObject JsonFile::get()
    {
        // @todo add error checking
        return m_json;
    }

    void JsonFile::setPath(QString t_path)
    {
        if(m_path == t_path)
        {
            return;
        }
        m_path = t_path;
    }
}

