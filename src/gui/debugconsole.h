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

    signals:
        void changeVisibility(bool state);
        void appendSignal(QString text);
        void clearSignal();
};

