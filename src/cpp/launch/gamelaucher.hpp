#pragma once

#include <QObject>

//! @namespace Namespace for classes and functions, related to key
//!            architecture and startup modules of application
namespace Application
{
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
            void launchFinished(bool result);
    };
} /// namespace Application;
