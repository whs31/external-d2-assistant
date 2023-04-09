#include "injector.hpp"

#include <QDebug>
#include <QTimer>
#include <windows.h>
#include <memory/memorytools.hpp>

using namespace Application;

Injector::Injector(QObject *parent)
    : QObject{parent}
{
}

void Injector::inject(const QString &dll_path, unsigned long pid, uint64_t time_before_inject_ms)
{
    qDebug().noquote() << "[INJECTOR] Selected .dll is" << dll_path << "to" << pid << "with delay of" << time_before_inject_ms;
    m_dll_path = dll_path;
    m_pid = pid;
    QTimer::singleShot(time_before_inject_ms, this, &Injector::injectL);
}

void Injector::injectL()
{
    QString path_in_windows_encoding = m_dll_path;
    path_in_windows_encoding.replace("/", "\\");
    LPCSTR _path = path_in_windows_encoding.toLocal8Bit().constData();
    DWORD _pid;
    HANDLE _handle;
    if(m_pid == Memory::base::processID)
    {
        _pid = Memory::base::processID;
        _handle = Memory::base::processHandle;
    }
    else
    {
        DWORD _pid = m_pid;
        HANDLE _handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _pid);
    }

    LPVOID p_dll = VirtualAllocEx(_handle, 0, strlen(_path) + 1, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(_handle, p_dll, (LPVOID)_path, strlen(_path) + 1, 0);
    HANDLE h_LoadThread = CreateRemoteThread(_handle, 0, 0,
                                             (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), p_dll, 0, 0);
    WaitForSingleObject(h_LoadThread, INFINITE);
    VirtualFreeEx(_handle, p_dll, strlen(_path) + 1 + 1, MEM_RELEASE);
    qInfo().noquote() << "[INJECTOR] Injected dll into" << _pid << ":" << _handle << "with load thread handle" << h_LoadThread;
}

