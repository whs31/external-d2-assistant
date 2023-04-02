#pragma once

#include <QObject>


class Entry : public QObject
{
    Q_OBJECT
public:
    explicit Entry(QObject *parent = nullptr);

    signals:

};
