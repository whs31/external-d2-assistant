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
    uintptr offset = 0x7ffef8fc6db0; // это временный оффсет для дебага, настоящие нужно искать
//    uintptr offset = (uintptr_t)0x300905a4d + (uintptr_t)0x43604A0 + (uintptr_t)0x8 * (uintptr_t)0x84 + (uintptr_t)0xa9c;
    qWarning() << Qt::hex << offset;
    qInfo() << Memory::read<float>(offset);
}
