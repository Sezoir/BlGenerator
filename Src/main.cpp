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

//    // Create container
//    RandContainer randContainer;

//    // Create the uniform int distro
//    randContainer.create(RandContainer::Distrobutions::UniformInt, 0, 100);

//    randContainer.create(RandContainer::Distrobutions::ExponentialDouble, 3.5);

//    qDebug() << randContainer.get<double>(RandContainer::Distrobutions::ExponentialDouble);
//    qDebug() << randContainer.get<int>(RandContainer::Distrobutions::UniformInt);

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
