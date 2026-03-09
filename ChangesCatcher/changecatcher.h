#ifndef CHANGECATCHER_H
#define CHANGECATCHER_H

#include "Commit.h"
#include "versionschain.h"

class ChangeCatcher
{
    /*
     * This class is responsible for finding of changes by comparing them with given previous state
     * and then generating new commit
     */
private:
    std::string pathToProject;
    UTILS::VersionsChain currentChain;
    bool compareCheck (); //checks if there is a change in comparison with version from chain
public:
    ChangeCatcher(std::string path, UTILS::VersionsChain chain) : pathToProject(path), currentChain(chain);
    std::pair <UTILS::Message, UTILS::Commit> generateCommit();
    ~ChangeCatcher();
};

#endif // CHANGECATCHER_H
