#ifndef BRANCH_H
#define BRANCH_H
#include "Commit.h"
#include "UTILS/headers/Message.h"
#include <string>
#include <vector>
#include <map>


class Branch
{
private:
    std::string branchName;
    std::vector<Commit> commits;
    std::string BRANCH_HEAD;
public:
    Branch(const std::string& name);

    // creates commit from HEAD and current changes
    Commit createCommit(const std::string& author, const std::string& message, const std::string& repoPath);
    // Returns to state of <commitID>
    void checkoutCommit(const std::string& commitID, const std::string& repoPath);
    Commit getLatestCommit() const;
    // copies branhc to path
    void saveBranch(const std::string& path);
    // loads branch from path
    static Branch loadBranch(const std::string& path);
};


#endif // BRANCH_H
