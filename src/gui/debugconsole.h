#pragma once

#include <QObject>

class DebugConsole : public QObject
{
    Q_OBJECT
public:
    explicit DebugConsole(QObject *parent = nullptr);
    Q_INVOKABLE void show();
    Q_INVOKABLE void hide();
    void append(QString text);
    void clear();
    Q_INVOKABLE void sendCommand(QString command);

    signals:
        void changeVisibility(bool state);
        void appendSignal(QString text);
        void clearSignal();
private:
    const QString COMMANDS[64] = { "quit" };
};

