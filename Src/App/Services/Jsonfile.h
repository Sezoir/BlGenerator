#pragma once

// Qt Libs
#include <QString>
#include <QJsonObject>

namespace App::Services {
    class JsonFile
    {
    public:
        /**
         * Contructor
         */
        JsonFile();

        /**
          * Destructor
          */
        ~JsonFile() = default;

        /**
         * @brief Loads the file and store json object in m_json.
         * @param t_path: Path to file.
         * @return bool: True if load is successful.
         *               False if a error occurs.
         */
        bool load(QString t_path);

        /**
         * @brief Updates m_json and then writes the json object to the json file.
         * @param t_json: The updated QJsonObject.
         * @return bool: True if successfull.
         *               False if a error occurs.
         */
        bool update(QJsonObject t_json);

        /**
         * @brief Returns a copy of the m_json.
         * @return QJsonObject: Value of m_json.
         */
        QJsonObject get();

        /**
         * @brief Sets the path of the file to be read/updated.
         * @param QString: Path string to the file.
         */
        void setPath(QString t_path);

    protected:
        QString m_path;
        QJsonObject m_json;
    };
}

