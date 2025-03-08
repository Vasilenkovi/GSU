#ifndef REPOSITORYKEEPER_H
#define REPOSITORYKEEPER_H
#include "repository.h"
#include <string>
#include <vector>
#include <map>



class RepositoryKeeper {
private:
    std::vector<std::string> pathsToRepositories;
    std::map<std::string, std::string> repos;
    std::map<std::pair<std::string, std::string>, std::string> hashes;

public:
    Repository invokeRepository(const std::string& repository);
    bool encryptAndSave(Repository repo);
    bool acceptCommand(const std::string& command, const std::string& repositoryName);
    bool commit(const std::string& description);
    bool addFile(const std::string& path);
    bool removeFile(const std::string& path);
    bool makeBranch(const std::string& name);
    bool switchToBranch(const std::string& name);
    bool deleteBranch(const std::string& name);
    bool blame(const std::string& repositoryName);
    bool switchToVersion(const std::string& versionHash);
    bool applyDiffs(const std::vector<Diff>& diffs);
    bool deleteCommit(const std::string& commitHash);
    bool createRepo(const std::string& path);
};

#endif // REPOSITORYKEEPER_H
