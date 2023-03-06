#include "loop.h"

#include <windows.h>
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

    Memory::linkToProcess("dota2.exe");
}

void Loop::tick()
{
    uintptr offset = 0x275BBA60C14; // это временный оффсет для дебага, настоящие нужно искать
    qInfo() << Memory::read<float>(offset);
}
