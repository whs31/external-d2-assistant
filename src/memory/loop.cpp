#include "loop.h"
#include "memory.h"

#include <QDebug>

Loop::Loop(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Loop::tick);

    timer->setInterval(200);
    timer->start();
}

void Loop::tick()
{
    DWORD processId = Memory::getProcessID("dota2.exe");

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);

    float currentMana = 0;
    uintptr_t hp_bar_offset = 0x2984F6A03D4;

    bool _try = ReadProcessMemory(hProcess, (BYTE*)hp_bar_offset, &currentMana, sizeof(float), nullptr);
    if(not _try)
        qCritical() << GetLastError();

    qInfo() << "Current mana of the hero: " << currentMana << "PID: " << processId;
}
