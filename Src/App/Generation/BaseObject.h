#pragma once

#include <QString>

namespace App::Generation
{
    struct BaseObject
    {
        enum class Type
        {
            Weapon,
            Shield,
            GrenadeMod,
            ClassMod,
            Error

        };

        QString typeToString(Type type)
        {
            switch(type)
            {
            case Type::Weapon:
                return QStringLiteral("Weapon");
            case Type::Shield:
                return QStringLiteral("Shield");
            case Type::GrenadeMod:
                return QStringLiteral("GrenadeMod");
            case Type::ClassMod:
                return QStringLiteral("ClassMod");
            case Type::Error:
                return QStringLiteral("Error");
            }

            return QStringLiteral("Error");
        }

        Type stringToType(QString type)
        {
            if(type == "Weapon")
                return Type::Weapon;
            if(type == "Shield")
                return Type::Shield;
            if(type == "GrenadeMod")
                return Type::GrenadeMod;
            if(type == "ClassMod")
                return Type::ClassMod;
            return Type::Error;
        }

        BaseObject(Type type, QString rarity, QString rarityColor, int lvl)
            : m_type(type)
            , m_rarity(rarity)
            , m_rarityColor(rarityColor)
            , m_lvl(lvl)
        {

        }

        Type m_type;
        QString m_rarity;
        QString m_rarityColor = "black";
        int m_lvl = -1;
    };
}
