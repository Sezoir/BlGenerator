#pragma once

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QVector>

// General structs that all types of loot may use
namespace App::Generation
{
    // All ability checks
    struct Ability
    {
        enum class Abilities
        {
            Strength,
            Dexterity,
            Constitution,
            Intelligence,
            Wisdom,
            Charisma,
            Elements,
            Error
        };

        Ability(Abilities abl) : m_ability(abl)
        {
            registerAbility(abl);
        }

        Ability(QString abl) : m_abilityString(abl)
        {
            registerAbility(abl);
        }

        Abilities m_ability;
        QString m_abilityString;

        void registerAbility(Abilities abl)
        {
            if(abl == Abilities::Strength)
                m_abilityString = "Str";
            else if(abl == Abilities::Dexterity)
                m_abilityString = "Dex";
            else if(abl == Abilities::Constitution)
                m_abilityString = "Con";
            else if(abl == Abilities::Intelligence)
                m_abilityString = "Int";
            else if(abl == Abilities::Wisdom)
                m_abilityString = "Wis";
            else if(abl == Abilities::Charisma)
                m_abilityString = "Cha";
            else if(abl == Abilities::Elements)
                m_abilityString = "Ele";
            else
            {
                qDebug() << "Error ability not valid: " << typeid(abl).name();
                m_abilityString = "Error";
            }
        }

        void registerAbility(QString abl)
        {
            if(abl == "Str")
                m_ability = Abilities::Strength;
            else if(abl == "Dex")
                m_ability = Abilities::Dexterity;
            else if(abl == "Con")
                m_ability = Abilities::Constitution;
            else if(abl == "Int")
                m_ability = Abilities::Intelligence;
            else if(abl == "Wis")
                m_ability = Abilities::Wisdom;
            else if(abl == "Cha")
                m_ability = Abilities::Charisma;
            else if(abl == "Ele")
                m_ability = Abilities::Elements;
            else if(abl == "Error")
                m_ability = Abilities::Error;
            else
            {
                qDebug() << "Error ability not valid: " << abl;
                m_ability = Abilities::Error;
            }
        }

        Abilities toAbility()
        {
            return m_ability;
        }

        QString toString()
        {
            return m_abilityString;
        }
    };
    // Represents a damage roll, i.e XdY where X = roll and Y = value
    struct Roll
    {
        int m_dice = 0;
        int m_value = 0;

        Roll() = default;

        static Roll create(QString dice)
        {
            // Check for empty string
            if(dice == "" || dice == "0d0")
                return Roll();

            // Check for the regular expression "xdy" where x and y are integers
            QRegularExpression re("\\d+[d]\\d+", QRegularExpression::CaseInsensitiveOption);
            if(!re.match(dice).hasMatch())
            {
                qDebug() << "Error dice shouldnt be : " << dice;
                exit(-1);
            }

            // Create roll
            Roll roll;
            // Split dice string by d to get 2 different integers
            QStringList list = dice.split("d");

            // Set values acording to split
            roll.m_value = list[0].toInt();
            roll.m_dice = list[1].toInt();
            return roll;
        }

        Roll operator+=(Roll & rhs)
        {
            if(this->m_dice == rhs.m_dice)
            {
                this->m_value += rhs.m_value;
                return *this;
            }
            return Roll();
        }

        QString toString() const
        {
            return QString::number(m_value) + "d" + QString::number(m_dice);
        }
    };

    /**
     * @brief The Damage struct
     * @param roll: The roll to be made
     * @param plusDamage: Constant additional damage
     * @param ability: The type of ability damage is based off
     */
    struct Damage
    {
        Damage(Roll roll, int plusDamage, Ability ability)
            : m_plusDamage(plusDamage)
            , m_ability(ability)
        {
            m_roll.append(roll);
        }

        Damage(QString damage, Ability ability)
            : m_ability(ability)
        {
            QRegularExpression re;
            re.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

            // Check for zero damage
            re.setPattern("([0]+[d][0]+)([+][0]+)?");
            if(re.match(damage).hasMatch() || damage == "")
            {
                m_roll.append(Roll::create("0d0"));
                m_plusDamage = 0;
                return;
            }

            // Check for the regular expression "xdy" where x and y are integers
            re.setPattern("\\d+[d]\\d+[+]\\d+");

            if(re.match(damage).hasMatch())
            {
                QStringList splitDamage = damage.split("+");
                m_roll.append(Roll::create(splitDamage.first()));
                m_plusDamage = splitDamage.last().toInt();
                return;
            }

            // Check for the regular expression "xdy" where x and y are integers
            re.setPattern("\\d+[d]\\d+");

            if(re.match(damage).hasMatch())
            {
                m_roll.append(Roll::create(damage));
                m_plusDamage = 0;
                return;
            }

            qDebug() << "Error with creation of damage" << "\nTry checking your json file damage properties";
            exit(-1);
        }

        Damage(int damage, Ability ability)
            : m_plusDamage(damage)
            , m_ability(ability)
        {
            m_roll.append(Roll::create("0d0"));
        }

        QVector<Roll> m_roll;
        int m_plusDamage = 0;
        Ability m_ability = Ability(Ability::Abilities::Error);

        Damage operator+=(Damage & rhs)
        {
            // Plus on plus damage
            this->m_plusDamage += rhs.m_plusDamage;
            // Check if roll has a 0d0 roll
            QVector<Roll>::iterator thisIt;

            for(thisIt = this->m_roll.begin(); thisIt != this->m_roll.end(); ++thisIt)
            {
                if(thisIt->m_value == 0 && thisIt->m_dice == 0)
                {
                    if(thisIt != this->m_roll.begin())
                        thisIt = this->m_roll.erase(thisIt);
                }
            }

            thisIt = this->m_roll.begin();

            // Check for same dice used, if so just sum of the value
            QVector<Roll>::iterator rhsIt;

            // Guard bool to stop duplicate of dice of same value;
            bool guard = true;

            for(rhsIt = rhs.m_roll.begin(); rhsIt != rhs.m_roll.end(); rhsIt++)
            {
                for(thisIt = this->m_roll.begin(); thisIt != this->m_roll.end(); thisIt++)
                {
                    if(thisIt->m_dice == rhsIt->m_dice)
                    {
                        thisIt->m_value += rhsIt->m_value;
                        guard = false;
                    }
                }

                if(guard)
                {
                    this->m_roll.append(rhs.m_roll);
                }
                else
                {
                    guard = true;
                }
            }

            return *this;
        }

        Damage operator+=(Roll & rhs)
        {
            // Check if roll has a 0d0 roll
            QMutableVectorIterator<Roll> i(this->m_roll);
            while(i.hasNext())
            {
                Roll & roll = i.next();
                if(roll.m_dice == 0 && roll.m_dice == 0)
                {
                    i.remove();
                    this->m_roll.append(rhs);
                }
            }

            // Check for same dice used, if so just sum of the value
            // Guard bool to stop duplicate of dice of same value;
            bool guard = true;

            QVector<Roll>::iterator it;
            for(it = this->m_roll.begin(); it != this->m_roll.end(); it++)
            {
                if(it->m_dice == rhs.m_dice)
                {
                    it->m_value += rhs.m_value;
                    guard = false;
                }
            }

            if(guard)
                this->m_roll.append(rhs);

            return *this;
        }

        Damage operator+=(QString rhs)
        {
            Damage damage = Damage(rhs, this->m_ability);
            *this += damage;
            return *this;
        }

        Damage operator+=(int rhs)
        {
            this->m_plusDamage += rhs;
            return *this;
        }

        QString toString()
        {
            QString str;
            foreach(const Roll & roll, m_roll)
                str.append(roll.toString() + " + ");
            str.append(QString::number(m_plusDamage) + "  " + m_ability.toString());
            return str;
        }
    };

    // Represents a element
    struct Element
    {
        Element(Damage damage,
                QString element,
                QVariantList effect,
                QString condition,
                int chance)
            : m_damage(damage)
            , m_element(element)
            , m_effects(effect)
            , m_condition(condition)
            , m_chance(chance)
        {

        }

        Element()
            : m_damage(Damage(0, Ability(Ability::Abilities::Error)))
        {

        }

        Damage m_damage;
        QString m_element = "";
        QVariantList m_effects;
        QString m_condition = "";
        int m_chance;

        Element operator+=(Damage rhs)
        {
            this->m_damage += rhs;
            return *this;
        }

        void addDamage(QString dmg)
        {
            m_damage += dmg;
        }

        void addDamage(int dmg)
        {
            m_damage += dmg;
        }

        void addChance(int chance)
        {
            m_chance += chance;
        }

        const QString getElement()
        {
            return m_element;
        }

        const QString toString()
        {
           auto i = m_damage.toString() + " " + m_element + "\n" + m_condition + "\n" + QString::number(m_chance);
           foreach(const QVariant & v, m_effects)
                i.append("\n" + v.toString());
           i.append("\n");
           return i;
        }

    };
}
