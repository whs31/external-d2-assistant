#include "gamelaucher.hpp"
#include "memory/memorytools.hpp"
#include <string>
#include <QString>
#include <QDebug>
#include <QProcess>

using namespace Application;

GameLauncher::GameLauncher(QObject *parent)
    : QObject{parent}
{}

void GameLauncher::launch()
{
    bool is_steam_launched = Memory::getProcessID("steam.exe") != 0;
    if(is_steam_launched)
        qInfo() << "[GAMELAUNCHER] Steam process found.";
    else
    {
        qCritical() << "[GAMELAUNCHER] Steam process not found. Program will not work correctly without Steam.";
        qCritical() << "[GAMELAUNCHER] Aborting launch.";
        return;
    }

    bool is_dota_launched = Memory::getProcessID("dota2.exe") != 0;

    QString dota_game_folder_path = QString::fromStdString(Memory::registry::getGamePath());
    dota_game_folder_path.replace("\\", "/");
    Memory::base::dotaGameFolder = dota_game_folder_path;
    qInfo().noquote() << "[GAMELAUNCHER] Found Dota 2 absolute path:" << dota_game_folder_path;

    Memory::base::dotaBinaryFolder = dota_game_folder_path + "bin/win64";
    Memory::base::dotaExecutable = Memory::base::dotaBinaryFolder + "/dota2.exe";
    qInfo().noquote() << "[GAMELAUNCHER] Found Dota 2 executable:" << Memory::base::dotaExecutable;

    if(not is_dota_launched)
    {
        QProcess::startDetached(Memory::base::dotaExecutable, { "-console", "-novid" });
        qInfo().noquote() << "[GAMELAUNCHER] Dota 2 launched from absolute path. Passing call stack to injector.";
        emit launchFinished(true);
        return;
    }

    qInfo() << "[GAMELAUNCHER] Dota 2 is already running. Passing call stack to injector.";
    qWarning() << "[GAMELAUNCHER] Some functions (like d+ patching) will not work correctly.";
    emit launchFinished(false);
}

