#include "debugconsole.h"
#include <QCoreApplication>

DebugConsole::DebugConsole(QObject *parent)
    : QObject{parent} {}

void DebugConsole::show()
{
    emit changeVisibility(true);
}

void DebugConsole::hide()
{
    emit changeVisibility(false);
}

void DebugConsole::append(QString text)
{

    emit appendSignal(text);
}

void DebugConsole::clear()
{
    emit clearSignal();
}

void DebugConsole::sendCommand(QString command)
{
    if(command == COMMANDS[0])
        QCoreApplication::quit();
}
