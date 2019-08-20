#pragma once

#include <QString>

namespace App::Generation
{
    struct BaseObject
    {
        BaseObject(QString type, QString rarity, int lvl)
            : m_type(type)
            , m_rarity(rarity)
            , m_lvl(lvl)
        {

        }
        QString m_type;
        QString m_rarity;
        int m_lvl = -1;
    };
}
