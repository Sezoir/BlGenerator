#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Bootstrap/Startup.h"

#include <QDebug>
#include "App/Services/RandContainer.h"

using namespace App::Services;

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    // Boot the applcation
    Bootstrap::Startup loader;

    // If successfull return event loop
    if (loader.success())
    {
        // State app loaded
        //qInfo(general) << "Application loaded";

        // Run event loop
        return app.exec();
    }

    return -1;
}
