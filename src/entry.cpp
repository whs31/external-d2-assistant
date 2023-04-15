#include "entry.hpp"
#include "launch/gamelaucher.hpp"
#include "launch/injector.hpp"
#include "memory/memorytools.hpp"
#include "staticconfig.h"

#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QTimer>

Entry::Entry(QObject *parent)
    : QObject{parent}
    , injector(new Application::Injector(this))
{
    Application::GameLauncher launcher;
    Memory::base::internalLib = QCoreApplication::applicationDirPath() + "/libinternal.dll";

    connect(&launcher, &Application::GameLauncher::launchFinished, this, [this](){
        injector->inject(Memory::base::internalLib, Memory::base::processID, Config::INJECT_DELAY);
    });

    launcher.launch();

    connect(injector, &Application::Injector::injectionFinished, this, &Entry::injected);
}

void Entry::injected(bool result)
{

}

