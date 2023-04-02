#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <qqml.h>
#include "launch/gamelaucher.hpp"

#include <Qonsole/debug.hpp>

QONSOLE_DECLARE;

int main(int argc, char *argv[])
{
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif
    QGuiApplication app(argc, argv);

    Q_INIT_RESOURCE(ui);
    QONSOLE_INIT;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    Application::GameLaucher launcher;
    launcher.launch();

    return app.exec();
}
