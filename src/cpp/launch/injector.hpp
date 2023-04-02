#pragma once

#include <QObject>


class Injector : public QObject
{
    Q_OBJECT
public:
    explicit Injector(QObject *parent = nullptr);

signals:

};
