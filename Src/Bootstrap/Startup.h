#pragma once

// Qt Libs
#include <QObject>
#include <QQmlApplicationEngine>

// Application
#include "../App/Application.h"

namespace Bootstrap {
    class Startup : public QObject
    {
        Q_OBJECT
    public:
        Startup();
        ~Startup() {}
        bool success() const { return this->m_isValid; }

    private:
        QQmlApplicationEngine & m_engine;
        QObject * m_root;
        bool m_isValid;
        App::Application & m_application;

        void configTheme();

        void loadMainView();

        explicit Startup(const Startup& rhs) = delete;
        Startup& operator= (const Startup& rhs) = delete;
    };
}
