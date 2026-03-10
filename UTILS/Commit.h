#ifndef COMMIT_H
#define COMMIT_H
#include <string>
#include <vector>
#include <map>
#include <stdint.h>
namespace UTILS {
    class Commit
    {
    private:
        std::string commitID;
        std::string parentID; //head before this commit
        std::string author;
        std::string date;
        std::string message;
        std::map<std::string, std::vector<uint8_t>> filesDiffs;

    public:
        Commit();
        static Commit fromBytes(const std::vector<uint8_t>& data);
        //Fills initial metadata
        void initMetadata(std::string parent, std::string author, std::string msg);
        // Добавляет diff для конкретного файла
        void addFileDiff(std::string filename, std::vector<uint8_t>);
        // saves commit to files ( branches/<branch_name>/commits/<commitID>.diff)
        void saveToFile(std::string path);
        // Loads diffs from files
        static Commit loadFromFile(std::string filepath);
        // ᓚ₍ ^. ̫ .^₎
        std::string getID() { return commitID; }
        // list of changes
        std::vector<std::string> getChangedFiles();
        std::string getParentID() const { return parentID; }
        const std::map<std::string, std::vector<uint8_t>>& getFilesDiffs() const { return filesDiffs; }
    };
}
#endif // COMMIT_H
