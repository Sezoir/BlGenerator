#pragma once

// Qt libs
#include <utility>
#include <map>
#include <stdexcept>
// Std libs
#include <QString>
#include <QDebug>
#include <QObject>

/**
 * View Factory
 *
 */
namespace Platform {
    template<class BASEMANAGER>
    class Factory : public QObject
    {
    public:

        explicit Factory(QObject * t_parent) : QObject(t_parent)
        {

        }

        ~Factory()
        {

        }

        Factory(const Factory&) = delete;


        /**
             * Minimal version of c++ is 11 standard
             * as such we'll impliment make_unique locally
             */
//        template<typename T, typename... Args>
//        std::unique_ptr<T> make_unique(Args&&... args)
//        {
//            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//        }


        /**
             * Create a new sensor instance
             *
             * @author Sam Mottley
             */
        template<typename T, typename... Args>
        QString create(QString view, Args && ... args)
        {
            // Create sensors as specified (std::make_unique c++14)
            //m_managers[view] = new T(std::forward<Args>(args) ...);
            //m_managers[view] = new T(args...);
            BASEMANAGER* p = new T(args...);
            m_managers.insert(std::pair<QString, BASEMANAGER*>(view, p));
            // Return the instance referance
            return view;
        }

        template<typename T,bool I, typename... Args>
        QString create(Args && ... args)
        {
            QString name(typeid(T).name());
            return create<T>(name, args...);
        }


        /**
             * Destroy an instance of an sensor
             *
             * @author Sam Mottley
             */
        void destroy()
        {
            if(m_managers.empty())
                return;

            // Erase the entry
            for(auto& i : m_managers)
            {
                delete i;
                i = nullptr;
                m_managers.erase(i.first);
            }
        }
        void destroy(QString view)
        {
            // Check exists
            exists(view);

            // Erase the entry
            m_managers.erase(view);
        }


        /**
             * Return a sensors object
             *
             * @author Sam Mottley
             * @param Type type supported sensor type
             * @param int i id of the sensor
             * @return T sensor class
             */
        template<typename T>
        T* get(QString view)
        {
            // Check exists
            exists(view);

            BASEMANAGER* tempBase = m_managers[view];
            return static_cast<T*>(tempBase);
        }

        template<typename T, bool I>
        T* get()
        {
            if(I == true)
            {
                QString name(typeid(T).name());

                return get<T>(name);
            }
            T * empty = nullptr;

            return empty;
        }

    private:
        // Container for all our sensors
        std::map<QString, BASEMANAGER*> m_managers;

        /**
             * Check ID exists
             *
             * @author Sam Mottley
             */
        void exists(QString view)
        {
            if (m_managers.find(view) == m_managers.end())
            {
                throw std::range_error("View does not exists.");
            }
        }

    };

}
