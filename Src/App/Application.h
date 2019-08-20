#pragma once

// Qt libs
#include <QObject>
#include <QQmlApplicationEngine>

// Settings class
#include "Settings/Settings.h"

// Loot Generation Class
#include "Generation/Generator.h"

// Common factory
#include "../Platform/QtFactory.h"

// Base controller class
#include "View/Controller.h"

namespace App {
    class Application : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief Application constructor
         * @param t_parent: QObject parent
         * @param t_engine: Application engine pointer
         */
        Application(QObject* t_parent, QQmlApplicationEngine * t_engine);

        /**
         * @brief Application Destructor
         */
        ~Application();

        // Delete copy assignment
        Application(Application &) = delete;
    private:

        // Engine
        QQmlApplicationEngine * m_engine;

        // Settings
        Settings::Settings & m_settings;

        // Loot generator
        Generation::Generator & m_generator;

        // Controller factory
        Platform::Factory<View::Controller> & m_controllerFactory;

        /**
         * @brief Creates all the views for the qml from the factory
         */
        void createManager();

        /**
         * @brief Registers all the view classes to the qml
         */
        void registerManager();

        /**
         * @brief Calls all the connectViews of the view classes.
         *        Subsequent classes connectViews will connect all the signals and slots for there own class.
         */
        void connectViews();
    };
}
