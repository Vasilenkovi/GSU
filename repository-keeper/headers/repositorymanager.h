#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H
#include <string>
#include <vector>
#include <map>


//list of possible operations
namespace OPS {
    //repository level operations
    const std::string NEW_REPO = "init";
    //branch level operations
    const std::string NEW_BRANCH = "new-branch";
    const std::string SELECT_BRANCH = "checkout";
    const std::string MERGE = "merge";
    // file level operations
    const std::string COMMIT = "commit";
    const std::string ADD_FILE = "add-file";
    const std::string DELETE_FILE = "delete-file";
}

//list of all permissions
namespace PERMS {
    const std::string ALL = "all";
    const std::string EDIT = "edit";
    const std::string VIEW = "view";
}

//list of standart roles
namespace ROLES {
    const std::string OWNER = "owner";
    const std::string CONTRIBUTOR = "contributor";
    const std::string VIEWER = "viewer";
}

class RepositoryManager {
private:
    std::map<std::string, std::string> permissions;
    RepositoryKeeper repositories;
    std::string installationPath;

public:
    void addToPath();
    bool processCommand(const std::string& command);
    void invokeRepositoryKeeper();
    void executeCommand(const std::string& command);
    void finishWork();
    void encryptAndSave();
    bool processRequest(const std::string& request);
};

#endif // REPOSITORYMANAGER_H
