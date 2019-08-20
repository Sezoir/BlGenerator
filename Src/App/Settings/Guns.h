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
    class Guns : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief Guns constructor
         * @param parent
         * @param t_Dir
         */
        explicit Guns(QObject *parent, QString t_Dir);

        /**
         * @brief ~Guns destructor
         */
        ~Guns() = default;

        /**
         * @brief Returns a copy of the variant map of total settings.
         * @return QVariantMap: Copy of the variant map of m_settings.
         */
        QVariantMap settings();

        /**
         * @brief Returns a copy of the variant map of elements.
         * @return QVariantMap: Copy of the variant map of elements from m_settings.
         */
        QVariantMap elements();

        /**
         * @brief Returns a copy of the variant map of manufactureres.
         * @return QVariantMap: Copy of the variant map of manufactureres from m_settings.
         */
        QVariantMap manufacturers();

        /**
         * @brief Returns a copy of the variant map of types.
         * @return QVariantMap: Copy of the variant map of ranged types from m_settings.
         */
        QVariantMap types();

        /**
         * @todo
         * @brief setManufacturers
         * @param t_map
         * @return
         */
        bool setManufacturers(QVariantMap & t_map);

    private:
        QVariantMap m_settings;
        QString m_Dir;

        /**
         * @brief Reads the settings from file
         */
        void readSettings();

    };
}
