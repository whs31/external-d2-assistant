#pragma once

#include <QObject>
#include <QTimer>

class Loop : public QObject
{
    Q_OBJECT
public:
    explicit Loop(QObject *parent = nullptr);

private:
    QTimer* timer;

    private slots:
        void tick();

signals:

};

