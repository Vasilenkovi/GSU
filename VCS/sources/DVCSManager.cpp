#include <QCoreApplication>
#include <filesystem>
#include <QDir>
#include <QDebug>
#include "VCS/headers/DVCSManager.h"
#include "UTILS/dirUtils.h"

DVCSManager::DVCSManager(std::string installationPath) {
    this->installationPath = installationPath;
    this->currentPath = QDir::currentPath();
    Message startUpStatus = this->checkEnv();
    if (startUpStatus.getBooleanStatus()==false)
    {
        qDebug() << startUpStatus.getFormattedMessage();
    }
}


Message DVCSManager::checkEnv()
{
    /*
     * Checks following files in INSTALLATION PATH:
     * 1) Existence of ./.networkLogs.json
     * 2) Existence of ./.vcsLogs.json
     * 3) Existence of ./.registeredRepos.json
     */
    // List of required files
    std::vector<std::string> requiredFiles = {
        ".networkLogs.json",
        ".vcsLogs.json",
        ".registeredRepos.json"
    };
    Message envStatus = dirUtils::checkFiles(requiredFiles, this->name, this->installationPath, statusMaps::WARNING);
    // Checking each file
    if (envStatus.getBooleanStatus()==false)
    {
        envStatus.setAdvice("Check missing files, maybe you accidentally deleted them or moved .exe to another directory");
    }
    return envStatus;
}
