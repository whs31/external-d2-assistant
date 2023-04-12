#pragma once

#include <QObject>

//! @brief
#define CONSOLE_DECLARE QONSOLE_DECLARE_PRIVATE

//! @brief
#define CONSOLE_INIT QONSOLE_INIT_PRIVATE

class ConsolePrivate;
class Console : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Console)

    public:
        explicit Console(QObject* parent = nullptr);

        //! @brief
        void append(const QString& message);

        //! @brief
        void sendCommand(const QString& command);

    protected:
        ConsolePrivate* const d_ptr;
};


















#define QONSOLE_DECLARE_PRIVATE QScopedPointer<Console> console; \
                        bool _init_ = false; \
                        void consoleHandler(QtMsgType type, const QMessageLogContext&, const QString& msg) \
                        { \
                            QString txt; \
                            int msgt = 0; \
                            switch (type) { \
                            case QtDebugMsg: \
                                txt = QString("%1").arg("<font color=\"#ECEFF4\">" + msg + "</font>"); \
                                msgt = 0; \
                                break; \
                            case QtWarningMsg: \
                                txt = QString("%1").arg("<font color=\"#EBCB8B\">" + msg + "</font>"); \
                                msgt = 2; \
                                break; \
                            case QtInfoMsg: \
                                txt = QString("%1").arg("<font color=\"#8FBCBB\">" + msg + "</font>"); \
                                msgt = 1; \
                                break; \
                            case QtCriticalMsg: \
                                txt = QString("%1").arg("<font color=\"#BF616A\">" + msg + "</font>"); \
                                msgt = 3; \
                                break; \
                            case QtFatalMsg: \
                                txt = QString("%1").arg("<font color=\"#D08770\">" + msg + "</font>"); \
                                msgt = 4; \
                                break; \
                            } \
                            if(_init_) \
                            console->append(txt); }

#define QONSOLE_INIT_PRIVATE console.reset(new Console()); \
                    _init_ = true; \
                    qInstallMessageHandler(consoleHandler);
