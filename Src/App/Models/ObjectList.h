#pragma once

// Qt libs
#include <QObject>
#include <QVector>

// Std libs
#include <memory>

// Base object struct
#include "../Generation/BaseObject.h"

// Weapon object struct
#include "../Generation/Weapon/Object.h"

namespace App::Models {
    class ObjectList : public QObject
    {
        Q_OBJECT
    public:
        explicit ObjectList(QObject *parent = nullptr);

        QVector<std::shared_ptr<Generation::BaseObject>> items() const;

        void addItem(std::shared_ptr<Generation::BaseObject> item);

        bool setItemAt(int index, const std::shared_ptr<Generation::BaseObject> & item);

    signals:
        void preItemAppended();
        void postItemAppended();

        void preItemRemoved(int index);
        void postItemRemoved();

    public slots:
        //void appendItem();

        void removeItems();

    private:
        QVector<std::shared_ptr<Generation::BaseObject>> m_Items;
    };
}

