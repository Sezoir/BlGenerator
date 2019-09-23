#include "ObjectList.h"

#include <QDebug>

namespace App::Models {
    ObjectList::ObjectList(QObject *parent) : QObject(parent)
    {

    }

    QVector<std::shared_ptr<Generation::BaseObject>> ObjectList::items() const
    {
        return m_Items;
    }

    void ObjectList::addItem(std::shared_ptr<Generation::BaseObject> item)
    {
        emit preItemAppended();

        m_Items.append(item);

        emit postItemAppended();
    }

    bool ObjectList::setItemAt(int index, const std::shared_ptr<Generation::BaseObject> &item)
    {
        if(index < 0 || index >= m_Items.size())
            return false;

        //@todo check current item at position to be the same as new item in position,
        // if so then return false
        //const Generation::BaseObject & oldItem = m_Items.at(index);

        m_Items[index] = item;

        return true;
    }

    void ObjectList::removeItems()
    {
        for(int i = 0; i < m_Items.size(); i++)
        {
            emit preItemRemoved(i);

            m_Items.removeAt(i);

            emit postItemRemoved();
        }
    }



}
