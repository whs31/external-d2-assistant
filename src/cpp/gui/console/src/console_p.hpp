#pragma once

#include "../console.hpp"
#include <QMap>
#include <functional>
#define __signal void

class ConsolePrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Console)
    Console* q_ptr;

    QMap<QString, std::function<void()>> command_list = {
        { "quit", [this](){ quit(); } },
        { "unload", [this](){ unload(); } },
        { "load", [this](){ load(); } }
    };

    public:
        ConsolePrivate(Console* parent);
        virtual ~ConsolePrivate() = default;

        Q_INVOKABLE void sendCommand(QString command);

        signals:
            __signal appendSignal(const QString& text);

    private:
        void quit();
        void unload();
        void load();
};
