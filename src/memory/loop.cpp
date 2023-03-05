#include "loop.h"
#include "memory.h"

#include <QDebug>

Loop::Loop(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Loop::tick);
    // @TODO: loop for process scan and etc ( 1 Hz, 5 Hz )

    // дота работает на частоте 40 Гц. Нет смысла ставить большую частоту,
    // так как значения между тиками будут интерполированы
    timer->setInterval(25);
    timer->start();
}

void Loop::tick()
{
    DWORD processId = Memory::getProcessID("dota2.exe");
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);

    float currentMana = 0;
    uintptr_t hp_bar_offset = 0x2984F6A03D4;

    bool _try = ReadProcessMemory(hProcess, (BYTE*)hp_bar_offset, &currentMana, sizeof(float), nullptr);
    if(not _try)
        qCritical() << GetLastError();

    qInfo() << "Current mana of the hero: " << currentMana << "PID: " << processId;
}
