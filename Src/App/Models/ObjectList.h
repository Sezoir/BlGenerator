#pragma once

// Qt libs
#include <QObject>
#include <QVector>

// Base object struct
#include "../Generation/BaseObject.h"

namespace App::Models {
    class ObjectList : public QObject
    {
        Q_OBJECT
    public:
        explicit ObjectList(QObject *parent = nullptr);

        QVector<Generation::BaseObject> items() const;

        void addItem(Generation::BaseObject item);

        bool setItemAt(int index, const Generation::BaseObject & item);

    signals:
        void preItemAppended();
        void postItemAppended();

        void preItemRemoved(int index);
        void postItemRemoved();

    public slots:
        //void appendItem();

        void removeItems();

    private:
        QVector<Generation::BaseObject> m_Items;
    };
}

