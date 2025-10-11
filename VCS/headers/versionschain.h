#ifndef VERSIONSCHAIN_H
#define VERSIONSCHAIN_H
#include <string>
#include <vector>
#include <map>
#include <fstream>
class VersionsChain
{
public:
    VersionsChain();
    std::string getHead();
    void getVersion(std::string hash, std::string targetPath);
    void removeVersion();

private:
    std::map <std::string, std::string> diffsChain;
    std::string TAIL;
    std::string HEAD;
    void calculateDiffs(std::ifstream  newContent, std::ifstream oldContent);
    void applyChanges(std::string change, std::ofstream target);
};

#endif // VERSIONSCHAIN_H
