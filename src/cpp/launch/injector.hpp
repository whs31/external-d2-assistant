
#ifndef INJECTOR_HPP
#define INJECTOR_HPP


#include <QObject>


class Injector : public QObject
{
    Q_OBJECT
public:
    explicit Injector(QObject *parent = nullptr);

signals:

};

#endif // INJECTOR_HPP
