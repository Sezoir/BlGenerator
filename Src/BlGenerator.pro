# Set project as main app
TEMPLATE = app

QT += qml quick quickcontrols2

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
             App/Application.cpp \
             App/Generation/Generator.cpp \
             App/Generation/Weapon/BaseFactory.cpp \
             App/Generation/Weapon/Factory.cpp \
             App/Generation/Weapon/GunFactory.cpp \
             App/Generation/Weapon/MeleeFactory.cpp \
    App/Models/ObjectList.cpp \
    App/Models/ObjectModel.cpp \
             App/Services/Jsonfile.cpp \
             App/Settings/General.cpp \
             App/Settings/Guns.cpp \
             App/Settings/Melee.cpp \
             App/Settings/Settings.cpp \
             App/View/Generate.cpp \
             Bootstrap/Startup.cpp \
             main.cpp \

HEADERS += \
             App/Application.h \
             App/Generation/BaseObject.h \
             App/Generation/Generator.h \
             App/Generation/Properties.h \
             App/Generation/Weapon/BaseFactory.h \
             App/Generation/Weapon/Factory.h \
             App/Generation/Weapon/GunFactory.h \
             App/Generation/Weapon/MeleeFactory.h \
             App/Generation/Weapon/Object.h \
    App/Models/ObjectList.h \
    App/Models/ObjectModel.h \
             App/Services/Jsonfile.h \
             App/Services/RandContainer.h \
             App/Settings/General.h \
             App/Settings/Guns.h \
             App/Settings/Melee.h \
             App/Settings/Settings.h \
             App/View/Controller.h \
             App/View/Generate.h \
             Bootstrap/Startup.h \
             Platform/QtFactory.h \


RESOURCES += Resources/resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$OUT_PWD/../Libs/fluid/qml

# Add embed icons
CONFIG += fluid_resource_icons

# Configs for fluid framework
qtConfig(static) {
    QMAKE_LIBDIR += \
        $$OUT_PWD/../Libs/fluid/qml/Fluid/Core \
        $$OUT_PWD/../Libs/fluid/qml/Fluid/Controls \
        $$OUT_PWD/../Libs/fluid/qml/Fluid/Controls/Private \
        $$OUT_PWD/../Libs/fluid/qml/Fluid/Templates
    QTPLUGIN += \
        qsvg \
        fluidcoreplugin \
        fluidcontrolsplugin \
        fluidcontrolsprivateplugin \
        fluidtemplatesplugin
}


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Windows specific actions
win32 {
    # Bundle Fluid QML plugins with the application
    WINDEPLOYQT_OPTIONS = -qmldir $$OUT_PWD/../Libs/fluid/qml/Fluid
}

## Deploy fluid docs
#fluiddocs.files = $$OUT_PWD/../Libs/fluid/

## Register deployments
#INSTALLS += fluiddocs

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
