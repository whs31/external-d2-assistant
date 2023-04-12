#include "console_p.hpp"
#include <qqml.h>
#include <QCoreApplication>

Console::Console(QObject* parent)
    : QObject{parent}
    , d_ptr(new ConsolePrivate(this))
{
}

void Console::append(const QString& message)
{
    Q_D(Console);
    emit (d->appendSignal(message));
}

void Console::sendCommand(const QString& command)
{
    Q_D(Console);
    d->sendCommand(command);
}

ConsolePrivate::ConsolePrivate(Console* parent)
    : QObject{parent}
    , q_ptr(parent)
{
    qmlRegisterSingletonInstance("ConsoleWidget", 1, 0, "Impl", this);
}

void ConsolePrivate::sendCommand(QString command)
{
    command_list[command]();
}

void ConsolePrivate::quit()
{
    qInfo() << "[CONSOLE] Shutting down...";
    QCoreApplication::quit();
}

void ConsolePrivate::unload()
{
    qInfo() << "[CONSOLE] Unloading internal module.";
}

void ConsolePrivate::load()
{
    qInfo() << "[CONSOLE] Loading internal module.";
}
