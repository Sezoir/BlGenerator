#include "Application.h"

// Qt Libs
#include <QQmlContext>
#include <QString>
#include <QDebug>

// Include view controllers.
#include "View/Generate.h"

namespace App {
    Application::Application(QObject * t_parent, QQmlApplicationEngine * t_engine)
        :   QObject(t_parent)
        ,   m_engine(t_engine)
        ,   m_settings(*new Settings::Settings(t_parent))
        ,   m_generator(*new Generation::Generator(t_parent , m_settings))
        ,   m_controllerFactory(*new Platform::Factory<View::Controller>(t_parent))
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
        m_controllerFactory.create<View::Generate, true>(this, m_generator);
    }

    void Application::registerManager()
    {
        m_engine->rootContext()->setContextProperty("GenerateController", m_controllerFactory.get<View::Generate, true>());
    }

    void Application::connectViews()
    {
        m_controllerFactory.get<View::Generate, true>()->makeConnections();
    }

}
