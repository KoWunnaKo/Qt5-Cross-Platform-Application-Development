#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlListProperty>
#include "gameinterface.h"

Q_DECLARE_METATYPE(QQmlListProperty<GameInterface>)


int main(int argc, char *argv[])
{
    // Enable High Dpi Scaling because ....
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Create our application, which controls our event loop
    QGuiApplication app(argc, argv);

    // Create our QML application engine, which handles our QML
    QQmlApplicationEngine engine;
    // Load our `main.qml` page
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // Check to see if we loaded the file correctly
    if (engine.rootObjects().isEmpty())
        // if we didn't load correctly, exit the main loop with the error/integer, `-1`
        return -1;

    return app.exec();
}
