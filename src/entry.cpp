#include "entry.hpp"
#include "launch/gamelaucher.hpp"
#include "launch/injector.hpp"
#include "memory/memorytools.hpp"

#include <QCoreApplication>

Entry::Entry(QObject *parent)
    : QObject{parent}
    , injector(new Application::Injector(this))
{
    Application::GameLauncher launcher;
    Memory::base::internalLib = QCoreApplication::applicationDirPath() + "/libinternal.dll";

    connect(&launcher, &Application::GameLauncher::launchFinished, this, [this](){
        injector->inject(Memory::base::internalLib, Memory::base::processID, 15000);
    });

    launcher.launch();
}

