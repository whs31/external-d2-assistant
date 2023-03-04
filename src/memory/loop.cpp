#include "loop.h"
#include <QDebug>

#include <vector>
#include <Windows.h>
#include "memoryread.h"

Loop::Loop(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Loop::tick);

    timer->setInterval(200);
    timer->start();
}


struct Modules
{
    uintptr_t clientModule;
    uintptr_t serverModule;
} modules;

void Loop::tick()
{
    DWORD processId = GetProcId(L"dota2.exe");

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);

    modules.clientModule = GetModuleBaseAddress(processId, L"client.dll");
    modules.serverModule = GetModuleBaseAddress(processId, L"server.dll");

    qDebug() << "Found clientModule => 0x" << modules.clientModule;
    qDebug() << "Found serverModule => 0x" << modules.serverModule;

    uintptr_t heroPointer = modules.serverModule + 0x024F5EE8;

    qDebug() << "Found hero pointer => 0x" << heroPointer;

    std::vector<unsigned int> currentManaOffsets = {0x0, 0x1C0, 0x18, 0x658};
    uintptr_t currentManaAddress = FindDMAAddy(hProcess, heroPointer, currentManaOffsets);

    float currentMana = 0;

    //actual loop part

        ReadProcessMemory(hProcess, (BYTE*)currentManaAddress, &currentMana, sizeof(currentMana), nullptr);
        qInfo() << "Current mana of the hero: %.1f\r" << currentMana;
}
