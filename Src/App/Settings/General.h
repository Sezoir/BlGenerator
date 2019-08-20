#pragma once

// Qt Libs
#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QList>

// Read and writing to json files
#include "../Services/Jsonfile.h"

namespace App::Settings {
    class General : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief General constructor
         * @param parent
         * @param t_Dir
         */
        explicit General(QObject *parent, QString t_Dir);

        /**
         * @brief ~General destructor
         */
        ~General() = default;

        /**
         * @brief Returns a copy of the variant map of settings.
         * @return QVariantMap: Copy of the variant map of m_settings.
         */
        QVariantMap settings();

        /**
         * @brief Returns a copy of the variant map of manufactureres.
         * @return QVariantMap: Copy of the variant map of manufactureres from m_settings.
         */
        QVariantMap general();

        /**
         * @todo
         * @brief setManufacturers
         * @param t_map
         * @return
         */
        bool setGeneral(QVariantMap & t_map);

    private:
        QVariantMap m_settings;
        QString m_Dir;

        /**
         * @brief Reads the settings from file
         */
        void readSettings();

    };
}


