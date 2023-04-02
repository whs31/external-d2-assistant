#pragma once

#include <QObject>


//! @namespace Пространство имен для классов и функций, работающих
//!            с инициализацией и настройкой ключевых модулей программы.
namespace Application
{
    //! @brief
    class Injector : public QObject
    {
        Q_OBJECT
        public:
        explicit Injector(QObject *parent = nullptr);

        //! @brief Совершает инжект динамической библиотеки в процесс.
        //! @param dll_path - абсолютный путь в файловой системе к библиотеке.
        //! @param pid - ID процесса для инжекта.
        //! @param time_before_inject_ms - задержка перед инжектом после запуска функции.
        //!        По умолчанию задержка отсутствует.
        //! @sa    Функция посылает сигнал injectionFinished() по завершении, который
        //!        содержит флаг результата.
        void inject(const QString& dll_path, unsigned long pid, uint64_t time_before_inject_ms = 0);

            signals:
            //! @brief Сигнал, сообщающий o завершении инжекта.
            //! @param result - возвращает TRUE, если инжект успешен.
            void injectionFinished(bool result);
    };
}
