#include "Application.h"

// Qt Libs
#include <QQmlContext>
#include <QString>
#include <QDebug>
#include <QDir>

// Include view controllers.
#include "View/Generate.h"

namespace App {
    Application::Application(QObject * parent, QQmlApplicationEngine * engine)
        :   QObject(parent)
        ,   m_engine(engine)
        ,   m_settings(*new Settings::Settings(parent))
        ,   m_generator(*new Generation::Generator(parent, m_settings))
        ,   m_controllerFactory(*new Platform::Factory<View::Controller>(parent))
    {
        createManager();
        registerManager();
        connectViews();
    }

    Application::~Application()
    {
    }

    void Application::createManager()
    {
        //QString create(QString view, Args & ... args)
        //m_controllerFactory.create<View::Generate>("Generate", this, m_generator);
        m_controllerFactory.create<View::Generate, true>(this, m_engine, m_generator, m_settings);
    }

    void Application::registerManager()
    {
        // Register some strings to be used in qml
        m_engine->rootContext()->setContextProperty("applicationPath", QDir().currentPath());

        // Register views
        m_engine->rootContext()->setContextProperty("GenerateController", m_controllerFactory.get<View::Generate, true>());
    }

    void Application::connectViews()
    {
        m_controllerFactory.get<View::Generate, true>()->makeConnections();
    }

}
