#pragma once

#include <QObject>


class GameLaucher : public QObject
{
    Q_OBJECT
public:
    explicit GameLaucher(QObject *parent = nullptr);

    void launch();

    signals:
        void gameLaunched();
};
