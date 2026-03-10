#ifndef VERSIONSCHAIN_H
#define VERSIONSCHAIN_H
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Message.h"
#include "Commit.h"
#include <stdint.h>
namespace UTILS {
    class VersionsChain
    {
    public:
        VersionsChain(std::string pathToChainHeader);
        Message newHead(std::string commitID); //add commit
        std::pair<Message, std::vector<uint8_t>> getVersion(std::string commitID); // reasembles files in repository to a given state
        Message removeVersion(std::string commitID); //removes given commit and makes its parent head
        std::pair<Message, std::vector<uint8_t>> getHeadVersion(); //reasembles files in repository to the head state
        Message restoreCommit(std::string commitID, const std::string& projectPath);
    private:
        std::string TAIL_PATH;
        std::string HEAD_PATH;
        std::string branchPath() const;
        std::string commitsDir() const;
        std::pair<std::string, std::string> readHeadTail() const;
        bool writeHeadTail(const std::string& head, const std::string& tail) const;
        std::pair<Message, Commit> loadCommit(const std::string& hash) const;
    };
}
#endif // VERSIONSCHAIN_H
