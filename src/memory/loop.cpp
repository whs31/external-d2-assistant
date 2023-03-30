#include "loop.h"
#include "memory.h"
#include <QDebug>

#ifdef Q_OS_LINUX
#else
#include <windows.h>
#endif

Loop::Loop(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Loop::tick);
    // @TODO: loop for process scan and etc ( 1 Hz, 5 Hz )

    // дота работает на частоте 40 Гц. Нет смысла ставить большую частоту,
    // так как значения между тиками будут интерполированы
    timer->setInterval(1000);

}

void Loop::start()
{
    timer->start();
    //Memory::linkToProcess("dota2.exe");

}

void Loop::tick()
{
    // расскоментируй потом

    //uintptr entityListPtr = Memory::read<uintptr>(Memory::offsets.base.clientDll + 0x43604a0);
    //uintptr entityPtr = Memory::read<uintptr>(entityListPtr + 0x8 * 0x7E); // C_DOTA_BaseNPC (casts to CBase_Entity) 0xBFC - скорее всего hero id
    /* Проверил 3 разных энтити. Вот их индексы смещения (rax * 0x8), значение rax:
     * 0x7E - 1st   78 - 2nd    183 - 3rd
     * Возможно, между второй и третьей энтити заспавнились крипы))
     * Расстояния: 0x6 - 0x10B
     */
    //qDebug() << Qt::hex << offsetof(BaseNPC, heroID);
   // BaseNPC npc = Memory::read<BaseNPC>(entityPtr);

    //qInfo() << npc << ", Hero Name: " << Utility::getHeroNameByID(npc.heroID);
}
