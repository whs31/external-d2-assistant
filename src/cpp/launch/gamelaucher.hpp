#pragma once

#include <QObject>

//! @namespace Пространство имен для классов и функций, работающих
//!            с инициализацией и настройкой ключевых модулей программы.
namespace Application
{
    //! @class Класс для запуска игры и передачи информации в инжектор.
    class GameLaucher : public QObject
    {
    Q_OBJECT
    public:
        explicit GameLaucher(QObject *parent = nullptr);

        //! @brief Запускает игру, если она еще не запущена, и сообщает о
        //!        результате в инжектор через сигнал.
        void launch();

        signals:
            //! @brief Сигнал, сообщающий о запуске/нахождении запущенного процесса
            //!        игрового клиента.
            void gameLaunched();
    };
} /// namespace Application;
