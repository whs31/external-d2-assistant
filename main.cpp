#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <qqml.h>

#include <debug.hpp>

#include "src/memory/loop.hxx"

QONSOLE_DECLARE;

int main(int argc, char *argv[])
{
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif
    QGuiApplication app(argc, argv);

    #ifdef __linux__
        qSetMessagePattern("[%{time process}] "
                        "%{if-debug}\033[01;38;05;15m%{endif}"
                        "%{if-info}\033[01;38;05;146m%{endif}"
                        "%{if-warning}\033[1;33m%{endif}"
                        "%{if-critical}\033[1;31m%{endif}"
                        "%{if-fatal}F%{endif}"
                        "%{message}\033[0m");
    #elif _WIN32
        qSetMessagePattern("[%{time process}] %{message}");
    #endif

    QONSOLE_INIT;

    Loop loop;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    loop.start();

    return app.exec();
}
