#include "debugconsole.h"

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
