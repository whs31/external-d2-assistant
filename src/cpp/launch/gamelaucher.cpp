#include "gamelaucher.hpp"
#include "memory/memorytools.hpp"
#include <string>
#include <QString>
#include <QDebug>
#include <QProcess>

using namespace Application;

GameLaucher::GameLaucher(QObject *parent)
    : QObject{parent}
{}

void GameLaucher::launch()
{
    bool is_dota_launched = Memory::linkToProcess("dota2.exe");

    QString dota_game_folder_path = QString::fromStdString(Memory::registry::getGamePath());
    dota_game_folder_path.replace("\\", "/");
    Memory::base::dotaGameFolder = dota_game_folder_path;
    qInfo().noquote() << "[GAMELAUNCHER] Found Dota 2 absolute path:" << dota_game_folder_path;

    Memory::base::dotaBinaryFolder = dota_game_folder_path + "/bin/win64";
    Memory::base::dotaExecutable = Memory::base::dotaBinaryFolder + "/dota2.exe";
    qInfo().noquote() << "[GAMELAUNCHER] Found Dota 2 executable:" << Memory::base::dotaExecutable;

    if(not is_dota_launched)
    {
        QProcess::startDetached(Memory::base::dotaExecutable, { "-console" });
        qInfo().noquote() << "[GAMELAUNCHER] Dota 2 launched from absolute path. Passing call stack to injector.";
        emit launchFinished(false);
        return;
    }

    qInfo() << "[GAMELAUNCHER] Dota 2 is already running. Passing call stack to injector.";
    qWarning() << "[GAMELAUNCHER] Some functions (like d+ patching) will not work correctly.";
    emit launchFinished(true);
}

