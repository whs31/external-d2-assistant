#pragma once

#include <QObject>
#define __signal void

//! @namespace Namespace for classes and functions, related to key
//!            architecture and startup modules of application
namespace Application
{
    //! @brief Class for dynamic library injection
    class Injector : public QObject
    {
        Q_OBJECT
        public:
            explicit Injector(QObject *parent = nullptr);

            //! @brief Injects dynamic library into process
            //! @param dll_path - absolute path to .dll file
            //! @param pid - process ID for injection
            //! @param time_before_inject_ms - delay in ms before injection
            //!                                By default delay equals 0
            //! @sa    Function emits injectionFinished() signal with result
            //!        boolean flag after injection
            void inject(const QString& dll_path, unsigned long pid, uint64_t time_before_inject_ms = 0);

            signals:
                //! @brief Signal, emitted after injection
                //! @param result - equals TRUE if injection is successful
                __signal injectionFinished(bool result);

                //! @brief Signal, emitted when injection starts.
                __signal injectionStarted();

            private slots:
                void injectL();

        private:
            QString m_dll_path;
            unsigned long m_pid;
    };
} /// namespace Application;
