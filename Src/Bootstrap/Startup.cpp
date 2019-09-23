#include "Startup.h"

#include <QGuiApplication>
#include <QQuickStyle>
#include <QDir>
#include <QtQuickControls2>

namespace Bootstrap {
    Startup::Startup()
        : QObject(nullptr)
        ,   m_engine (*new QQmlApplicationEngine())
        ,   m_isValid(true)
        ,   m_application(*new App::Application(this, &m_engine))
    {
        // Add import paths for qml libs
        m_engine.addImportPath(QCoreApplication::applicationDirPath() + QDir::separator() +
                               QLatin1String("..") + QDir::separator() + QLatin1String("..") +
                               QDir::separator() + QLatin1String("Libs") + QDir::separator() +
                               QLatin1String("fluid") + QDir::separator() + QLatin1String("qml"));

        // Configure theme
        configTheme();

        // Load main view
        loadMainView();
    }

    void Startup::configTheme()
        {
            // Setup the styling
//            if (QQuickStyle::name().isEmpty())
//                QQuickStyle::setStyle(QLatin1String("Material"));
        }

    void Startup::loadMainView()
    {
        // Load the main application qml file
        m_engine.load(QUrl(QStringLiteral("qrc:/views/main.qml")));

        // Get root objects
        auto rootObjects = m_engine.rootObjects();

        // Validate
        if (rootObjects.isEmpty())
        {
            qDebug() << "There are no QML objects!";
            m_isValid = false;
            return;
        }

        // Save a pointer to the root objects
        m_root = rootObjects[0];
    }
}
