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
    class Melee : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief Melee constructor
         * @param parent
         * @param t_Dir
         */
        explicit Melee(QObject *parent, QString t_Dir);

        /**
         * @brief ~Melee destructor
         */
        ~Melee() = default;

        /**
         * @brief Returns a copy of the variant map of all settings.
         * @return QVariantMap: Copy of the variant map of m_settings.
         */
        QVariantMap settings();

        /**
         * @brief Returns a copy of the variant map of blades.
         * @return QVariantMap: Copy of the variant map of blades from m_settings.
         */
        QVariantMap parts();

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
         * @return QVariantMap: Copy of the variant map of types from m_settings.
         */
        QVariantMap types();

    private:
        QVariantMap m_settings;
        QStringList m_fileNames;
        QString m_Dir;

        /**
         * @brief Reads the settings from file
         */
        void readSettings();

    };
}


