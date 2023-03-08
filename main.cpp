#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <qqml.h>

#include "src/memory/loop.h"
#include "src/gui/debugconsole.h"

QScopedPointer<DebugConsole> console;
bool _init_ = false;

void consoleHandler(QtMsgType type, const QMessageLogContext&, const QString& msg)
{
    QString txt;
    int msgt = 0;
    switch (type) {
    case QtDebugMsg:
        txt = QString("%1").arg("<font color=\"#ECEFF4\">" + msg + "</font>");
        msgt = 0;
        break;
    case QtWarningMsg:
        txt = QString("%1").arg("<font color=\"#EBCB8B\">" + msg + "</font>");
        msgt = 2;
        break;
    case QtInfoMsg:
        txt = QString("%1").arg("<font color=\"#8FBCBB\">" + msg + "</font>");
        msgt = 1;
        break;
    case QtCriticalMsg:
        txt = QString("%1").arg("<font color=\"#BF616A\">" + msg + "</font>");
        msgt = 3;
        break;
    case QtFatalMsg:
        txt = QString("%1").arg("<font color=\"#D08770\">" + msg + "</font>");
        msgt = 4;
        break;
    }

    if(_init_)
        console->append(txt);
}

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

    console.reset(new DebugConsole);
    _init_ = true;
    qmlRegisterSingletonInstance<DebugConsole>("DebugConsoleImpl", 1, 0, "Impl", console.get());
    qInstallMessageHandler(consoleHandler);

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
