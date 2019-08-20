#include "Startup.h"

#include <QQuickStyle>

namespace Bootstrap {
    Startup::Startup()
        : QObject(nullptr)
        ,   m_engine (*new QQmlApplicationEngine())
        ,   m_isValid(true)
        ,   m_application(*new App::Application(this, &m_engine))
    {
        // Configure theme
        configTheme();

        // Load main view
        loadMainView();
    }

    void Startup::configTheme()
        {
            // Setup the styling
            if (QQuickStyle::name().isEmpty())
                QQuickStyle::setStyle(QLatin1String("Material"));
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
