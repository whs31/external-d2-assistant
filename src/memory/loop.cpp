#include "loop.h"

#include <windows.h>
#include "memory.h"

//#include "offsets/offsets.h"

#include <QDebug>

Loop::Loop(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Loop::tick);
    // @TODO: loop for process scan and etc ( 1 Hz, 5 Hz )

    // дота работает на частоте 40 Гц. Нет смысла ставить большую частоту,
    // так как значения между тиками будут интерполированы
    timer->setInterval(250);

}

void Loop::start()
{
    timer->start();
    Memory::linkToProcess("dota2.exe");
}

void Loop::tick()
{
    uintptr entityListPtr = Memory::read<uintptr>(Memory::offsets.base.clientDll + 0x43604a0);
    uintptr entityPtr = Memory::read<uintptr>(entityListPtr + 0x8 * 0x15);
    uintptr manaOffsetPtr =  entityPtr + 0xA9C;
    float mana = Memory::read<float>(manaOffsetPtr);
    qWarning() << Qt::hex << manaOffsetPtr;
    qInfo() << mana;
}
