#pragma once

#include <QObject>

class DebugConsole : public QObject
{
    Q_OBJECT
public:
    explicit DebugConsole(QObject *parent = nullptr);
    void show();
    void hide();
    void append(QString text);
    void clear();

    signals:
        void changeVisibility(bool state);
        void appendSignal(QString text);
        void clearSignal();
};

