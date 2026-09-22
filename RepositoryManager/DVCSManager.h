#ifndef DVCSMANAGER_H
#define DVCSMANAGER_H
#include <string>
#include <vector>
#include <map>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include "repositorykeeper.h"
#include "Message.h"

//all operations


//list of all permissions
namespace PERMS {
    enum class Permissions
    {
        ALL,
        EDIT,
        VIEW
    };
}

//list of standart roles
namespace ROLES {
    enum class RolesList
    {
        OWNER,
        CONTRIBUTOR,
        VIEWER
    };
}

class DVCSManager {
    /*
     * This class is entry point of VCS and responsible for the following tasks:
     * 1) Managment of files within system during network jobs
     * 2) Checking integrity of utility files
     * 3)
     */
private:
    std::string name = "Manager";
    std::map<std::string, std::string> permissions;
    std::vector <RepositoryKeeper> repositories; // List of keepers for repositories which are marked for network jobs
    std::string currentPath; // Current path of D&DVCS manager calling
    std::string installationPath;
public:
    DVCSManager(std::string installationPath); // collects data about INSTALLATION PATH and CURRENT PATH
    // Starting functions
    UTILS::Message checkEnv(); // This method checks integrity of utility files in INSTALLATION PATH
    std::vector<UTILS::Message> check_all_keepers(); // Checks the status of all keepers
    UTILS::Message createRepository(std::string pathToRepo); // Creates .DVCS_U directory and utility files within it for new repository in pathToRepo as well as link in root directory of D&DVCS manager
    UTILS::Message invokeRepositoryKeeper(std::string pathToRepo); // Deserialize repo keeper from utility file in DVCS_U
    UTILS::Message executeVCSCommand(std::string command); // For managing keepers
    UTILS::Message processRequest(std::string& request); // Handles and analyses (it is VCS command, network command or misc) request to the manager
    UTILS::Message finishWork(); // Finishes work of manager creates logs and initiates serialization of all info
    // Info functions
    std::string getCurrentPath() // Well it's obvious
    {
        return this->currentPath;
    }
    ~DVCSManager();
};

#endif // DVCSMANAGER_H
