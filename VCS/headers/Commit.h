#ifndef COMMIT_H
#define COMMIT_H
#include <string>
#include <vector>
#include <map>

class Commit
{
private:
    std::string commitID;
    std::string parentID;//head before this commit
    std::string author;
    std::string date;
    std::string message;
    std::map<std::string, std::string> fileDiffs;

public:
    Commit(std::string parent, std::string author, std::string msg);

    // Добавляет diff для конкретного файла
    void addFileDiff(const std::string& filename, const std::string& diffContent);

    // saves commit to files ( branches/<branch_name>/commits/<commitID>.diff)
    void saveToFile(const std::string& path);

    // Loads diffs from files
    static Commit loadFromFile(const std::string& filepath);

    std::string getID() const { return commitID; }

    // list of changes
    std::vector<std::string> getChangedFiles() const;
};
#endif // COMMIT_H
