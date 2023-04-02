#include "injector.hpp"

#include <QDebug>

using namespace Application;

Injector::Injector(QObject *parent)
    : QObject{parent}
{

}

void Injector::inject(const QString &dll_path, unsigned long pid, uint64_t time_before_inject_ms)
{
    qDebug().noquote() << "[INJECTOR] Selected .dll is" << dll_path << "to" << pid << "with delay of" << time_before_inject_ms;
}

