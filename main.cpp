#include "src/entry.hpp"
#include "gui/console/console.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <qqml.h>


CONSOLE_DECLARE;

int main(int argc, char *argv[])
{
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif
    QGuiApplication app(argc, argv);

    CONSOLE_INIT;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl)
                    {
                        if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
                    }
                    , Qt::QueuedConnection);
    engine.load(url);

    Entry entryPoint;

    return app.exec();
}
