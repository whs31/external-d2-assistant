#include "entry.hpp"
#include "launch/gamelaucher.hpp"
#include "launch/injector.hpp"
#include "memory/memorytools.hpp"

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
        injector->inject(Memory::base::internalLib, Memory::base::processID, 15000);
    });

    launcher.launch();

    connect(injector, &Application::Injector::injectionFinished, this, &Entry::injected);
}

void Entry::injected(bool result)
{
    QTimer::singleShot(1000, [this](){
        /// не работает, возвращает false
        const char* log_test = "sdihfbasuihdfbhjasdbfhj";
        PVOID lpReturn = NULL;
        qCritical() << "Try";
        /// не работает, не находит ModuleHandle
        bool ret = Memory::remoteFunction(Memory::base::processHandle, "libinternal.dll", "attachTest", (LPVOID)log_test, sizeof(log_test), &lpReturn);
        qDebug() << ret;

        ///  не работает, сегфолт
//            auto hLib = GetModuleHandleA("libinternal.dll");
//            auto fn = GetProcAddress(hLib, "attachTest");
//            ((bool(__stdcall*)(void))fn)();
    });
}

