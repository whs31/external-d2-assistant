#include "entry.hpp"
#include "launch/gamelaucher.hpp"
#include "launch/injector.hpp"
#include "memory/memorytools.hpp"

#include <QCoreApplication>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
    Application::GameLaucher launcher;
    Application::Injector injector;
    Memory::base::internalLib = QCoreApplication::applicationDirPath() + "/libinternal.dll";

    QObject::connect(&launcher, &Application::GameLaucher::launchFinished, this, [&injector](){
        injector.inject(Memory::base::internalLib, Memory::base::processID, 7500);
    });

    launcher.launch();
}

