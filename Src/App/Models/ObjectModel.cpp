#include "ObjectModel.h"

// Qt libs
#include <QDebug>

// Weapon object
#include "../Generation/Weapon/Object.h"

namespace App::Models {
    ObjectModel::ObjectModel(QObject *parent)
        : QAbstractListModel(parent)
        , m_list(nullptr)
    {

    }

    int ObjectModel::rowCount(const QModelIndex &parent) const
    {
        // For list models only the root node (an invalid parent) should return the list's size. For all
        // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
        if (parent.isValid() || !m_list)
            return 0;

        return m_list->items().size();
    }

    //        QString m_name;
    //        QString m_weaponType;
    //        QString m_weaponFocus;
    //        Damage m_rangedDamage = Damage(Roll::create("0d0"), 0, Ability("Error"));
    //        Damage m_meleeDamage = Damage(Roll::create("0d0"), 0, Ability("Error"));
    //        int m_rangeHit = 0;
    //        int m_meleeHit = 0;
    //        int m_range = 0;
    //        QString m_manufacturer;
    //        QVector<Element> m_elements;
    //        QVector<QString> m_effects;
    //        int m_ammo = 0;

    QVariant ObjectModel::data(const QModelIndex &index, int role) const
    {
        if (!index.isValid() || !m_list)
            return QVariant();

        std::shared_ptr<Generation::BaseObject> item = m_list->items().at(index.row());

        switch(item->m_type)
        {
        case Generation::BaseObject::Type::Weapon:
            return weaponData(item, role);
        case Generation::BaseObject::Type::Shield:
            break;
        case Generation::BaseObject::Type::GrenadeMod:
            break;
        case Generation::BaseObject::Type::ClassMod:
            break;
        }

//        switch(role)
//        {
//        case TypeRole:
//            return QVariant(item.m_type);
//        case RarityRole:
//            return QVariant(item.m_rarity);
//        case LevelRole:
//            return QVariant(item.m_lvl);
//        }

        return QVariant();
    }

    bool ObjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if(!m_list)
            return false;

        std::shared_ptr<Generation::BaseObject> item = m_list->items().at(index.row());
        switch(role)
        {
        case TypeRole:
            item->m_type = item->stringToType(value.toString());
            break;
        case RarityRole:
            item->m_rarity = value.toString();
            break;
        case LevelRole:
            item->m_lvl = value.toInt();
            break;
        case NameRole:
            qDebug() << "Error";
            break;
        }

        if (m_list->setItemAt(index.row(), item))
        {
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
        return false;
    }

    Qt::ItemFlags ObjectModel::flags(const QModelIndex &index) const
    {
        if (!index.isValid())
            return Qt::NoItemFlags;

        return Qt::ItemIsEditable;
    }

    QHash<int, QByteArray> ObjectModel::roleNames() const
    {
        QHash<int, QByteArray> names;
        names[TypeRole] = "type";
        names[RarityRole] = "rarity";
        names[LevelRole] = "level";
        names[NameRole] = "name";
        names[WeaponTypeRole] = "weaponType";
        names[WeaponFocusRole] = "weaponFocus";
        names[RangedDamageRole] = "rangedDamage";
        names[MeleeDamageRole] = "meleeDamage";
        names[RangedHitRole] = "rangedHit";
        names[MeleeHitRole] = "meleeHit";
        names[RangeRole] = "range";
        names[ManufacturerRole] = "manufacturer";

        names[AmmoRole] = "ammo";

          /*
                    WeaponTypeRole,
                    WeaponFocusRole,
                    RangedDamageRole,
                    MeleeDamageRole,
                    RangedHitRole,
                    MeleeHitRole,
                    RangeRole,
                    ManufacturerRole,
                    ElementsRole,
                    EffectsRole,
                    AmmoRole
           */
        return names;
    }

    ObjectList *ObjectModel::list() const
    {
        return m_list;
    }

    void ObjectModel::setList(ObjectList *list)
    {
        beginResetModel();

        if(m_list)
            m_list->disconnect(this);

        m_list = list;

        if(m_list)
        {
            connect(m_list, &ObjectList::preItemAppended, this, [=]() {
                const int index = m_list->items().size();
                beginInsertRows(QModelIndex(), index, index);
            });
            connect(m_list, &ObjectList::postItemAppended, this, [=]() {
                endInsertRows();
            });
            connect(m_list, &ObjectList::preItemRemoved, this, [=](int index) {
                beginRemoveRows(QModelIndex(), index, index);
            });
            connect(m_list, &ObjectList::postItemRemoved, this, [=]() {
                endRemoveRows();
            });
        }

        endResetModel();
    }

    QVariant ObjectModel::weaponData(std::shared_ptr<Generation::BaseObject> item, int role) const
    {
        auto weapon = std::static_pointer_cast<Generation::Weapon::Weapon>(item);

        switch(role)
        {
        case TypeRole:
            return QVariant(weapon->typeToString(weapon->m_type));
        case RarityRole:
            return QVariant(weapon->m_rarity);
        case LevelRole:
            return QVariant(weapon->m_lvl);
        case NameRole:
            return QVariant(weapon->m_name);
        case WeaponTypeRole:
            return QVariant(weapon->m_weaponType);
        case WeaponFocusRole:
            return QVariant(weapon->m_weaponFocus);
        case RangedDamageRole:
            return QVariant(weapon->m_rangedDamage.toString());
        case MeleeDamageRole:
            return QVariant(weapon->m_meleeDamage.toString());
        case RangedHitRole:
            return QVariant(weapon->m_rangeHit);
        case MeleeHitRole:
            return QVariant(weapon->m_meleeHit);
        case RangeRole:
            return QVariant(weapon->m_range);
        case ManufacturerRole:
            return QVariant(weapon->m_manufacturer);
        case AmmoRole:
            return QVariant(weapon->m_ammo);
        }
    }

}
