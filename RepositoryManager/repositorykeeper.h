#ifndef REPOSITORYKEEPER_H
#define REPOSITORYKEEPER_H

#include <string>
#include <vector>
#include <map>
#include <QFile>
#include <QDataStream>
#include <utility>
#include "Message.h"
#include "Branch.h"
#include "Commit.h"


namespace ReposOps {
    // one day i will use it to store command types
}

class RepositoryKeeper {
    /*
     * Object of this class represents one repository and responsible for the following tasks:
     * 1) Managment of files within DVCS_U
     * 2) Manage Branches
     * 3) Handling of VSC commands for repo
     * ------------------------------------
     * Works with following files
        .repokeep/
        ├─ snaps/
        ├─ branches/
        │   └─ <branch_name>/
        │       ├─ commits/  (all commit.diff as list of files)
        │       └─ meta/     (directory for all metadata of commits)
     */
private:
    std::string pathToRepository; // current path to the repository
    std::string checkPathToRepository(); // checks and if needed changes current pathToRepository
    std::string invokedWithPermissions; // permissions received from manager
    std::pair<std::string, std::string> HEADS; // commit and branch
public:
    RepositoryKeeper( std::string& repositoryPath); // constructor - check repository service files
    UTILS::Message checkEnv();
    UTILS::Message acceptCommand( std::string& command, std::map<char, std::string> flags);
    // accepts command and invokes one of the methods to handle it, returns message with the status
    UTILS::Commit stageChanges( std::string& description);
    UTILS::Message makeBranch( std::string& name);
    UTILS::Message switchToBranch( std::string& name);
    UTILS::Message deleteBranch( std::string& name);
    std::string blame( std::string& repositoryName);
    UTILS::Message switchToVersion( std::string& versionID);
    UTILS::Message deleteCommit( std::string& commitID);
};

#endif // REPOSITORYKEEPER_H
