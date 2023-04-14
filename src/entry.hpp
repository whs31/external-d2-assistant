#pragma once

#include <QObject>
#define __signal void

namespace Application {
    class Injector;
}

class Entry : public QObject
{
    Q_OBJECT

    Application::Injector* injector;

    public:
        explicit Entry(QObject *parent = nullptr);

        signals:

};
