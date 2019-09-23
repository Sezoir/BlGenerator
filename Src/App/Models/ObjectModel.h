#pragma once

// Qt libs
#include <QAbstractListModel>
#include "ObjectList.h"

namespace App::Models {
    class ObjectModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(ObjectList * list READ list WRITE setList)

    public:
        explicit ObjectModel(QObject *parent = nullptr);

        enum {
            TypeRole = Qt::UserRole,
            RarityRole,
            LevelRole,
            NameRole,
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
        };

        // Basic functionality:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        // Editable:
        bool setData(const QModelIndex &index, const QVariant &value,
                     int role = Qt::EditRole) override;

        Qt::ItemFlags flags(const QModelIndex& index) const override;

        virtual QHash<int, QByteArray> roleNames() const override;

        ObjectList *list() const;
        void setList(ObjectList *list);

    private:
        ObjectList *m_list;

        QVariant weaponData(Generation::BaseObject * item, int role) const;

    };
}
