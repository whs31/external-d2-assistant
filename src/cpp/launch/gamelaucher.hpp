#pragma once

#include <QObject>
#include <list>
#define __signal void

//! @namespace Namespace for classes and functions, related to key
//!            architecture and startup modules of application
namespace Application
{
    static std::list<QString> launch_arguments;

    //! @class Class, which is responsible for launching game
    class GameLauncher : public QObject
    {
        Q_OBJECT

        public:
            explicit GameLauncher(QObject *parent = nullptr);

            //! @brief Launches game, if not launched, and emits signal after launch
            //! @sa    Emits launchFinished() after launching, which contains boolean
            //!        result of function execution
            void launch();

            signals:
                //! @brief Signal, emitted after launching game
                //! @param result - equals TRUE if launching is successful,
                //!        FALSE if game is already launched
                __signal launchFinished(bool result);
    };
} // namespace Application;
