#ifndef REPOSITORYFILE_H
#define REPOSITORYFILE_H
#include "versionschain.h"
#include <string>
#include <vector>
#include <map>

class Repository {
private:
    std::string hash;
    std::map<std::string, std::string> fileToHash;
    std::vector<std::string> rolesToAccessRepo;
    std::map<std::string, std::string> rolesToAccessFiles;
    std::string pathToTheDiffs;
    Branch* currentBranch;
    std::string metadataPath;
    std::string pathToRoot;
    std::string lastVersionPath;
    std::string pathToTheBranch;

public:
    bool commit();
    bool removeFile(const std::string& path);
    void goFromTo(const std::string& start, const std::string& version);
    void deleteFromVersionChain();
};

#endif // REPOSITORYFILE_H
