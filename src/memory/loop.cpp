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
    DWORD processId = getProcessID("dota2.exe");

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);

    float currentMana = 0;
    uintptr_t hp_bar_offset = 0x2984F6A03D4;

    bool _try = ReadProcessMemory(hProcess, (BYTE*)hp_bar_offset, &currentMana, sizeof(float), nullptr);
    //if(not _try)
        //qDebug() << GetLastError();

    qInfo() << "Current mana of the hero: " << currentMana;
}
