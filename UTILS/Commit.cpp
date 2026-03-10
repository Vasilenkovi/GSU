#include "Commit.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#include <cstring>
#include <iomanip>

namespace UTILS {

Commit::Commit() : commitID(""), parentID(""), author(""), date(""), message("") {}

void Commit::initMetadata(std::string parent, std::string author, std::string msg) {
    this->parentID = parent;
    this->author = author;
    this->message = msg;

    // Date is set up in format YYYY-MM-DD HH:MM:SS TODO: Check later consistency of data format in project
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    this->date = ss.str();

    // Hash from meta data + random(gamba)
    std::hash<std::string> hasher;
    size_t hash = hasher(parent + author + date + message + std::to_string(rand()));
    this->commitID = std::to_string(hash);
}

void Commit::addFileDiff(std::string filename, std::vector<uint8_t> diff) {
    filesDiffs[filename] = std::move(diff);
}

void Commit::saveToFile(std::string path) {
    std::ofstream file(path, std::ios::binary);
    if (!file) return;

    // Identifier of format
    const char magic[8] = {'C', 'O', 'M', 'M', 'I', 'T', '\0', '\0'};
    file.write(magic, 8);

    // Version of format(:clueless: just for a good manners) (uint32_t)
    uint32_t version = 1;
    file.write(reinterpret_cast<const char*>(&version), sizeof(version));

    // commitID (длина + строка)
    uint32_t len = commitID.size();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(commitID.c_str(), len);

    // parentID
    len = parentID.size();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(parentID.c_str(), len);

    // author
    len = author.size();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(author.c_str(), len);

    // date
    len = date.size();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(date.c_str(), len);

    // message
    len = message.size();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(message.c_str(), len);

    // Amount of files
    uint32_t fileCount = filesDiffs.size();
    file.write(reinterpret_cast<const char*>(&fileCount), sizeof(fileCount));

    for (const auto& [fname, delta] : filesDiffs) {
        len = fname.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(fname.c_str(), len);

        uint32_t deltaSize = delta.size();
        file.write(reinterpret_cast<const char*>(&deltaSize), sizeof(deltaSize));
        file.write(reinterpret_cast<const char*>(delta.data()), deltaSize);
    }
}

Commit Commit::loadFromFile(std::string filepath) {
    Commit commit;
    std::ifstream file(filepath, std::ios::binary);
    if (!file) return commit; // TODO incorporate Messages

    // Check file header
    char magic[8];
    file.read(magic, 8);
    if (std::memcmp(magic, "COMMIT\0\0", 8) != 0) return commit;

    // Version ))
    uint32_t version;
    file.read(reinterpret_cast<char*>(&version), sizeof(version));
    if (version != 1) return commit;

    auto readString = [&file]() -> std::string {
        uint32_t len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string str(len, '\0');
        file.read(&str[0], len);
        return str;
    };

    commit.commitID = readString();
    commit.parentID = readString();
    commit.author = readString();
    commit.date = readString();
    commit.message = readString();

    uint32_t fileCount;
    file.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));

    for (uint32_t i = 0; i < fileCount; ++i) {
        std::string fname = readString();

        uint32_t deltaSize;
        file.read(reinterpret_cast<char*>(&deltaSize), sizeof(deltaSize));
        std::vector<uint8_t> delta(deltaSize);
        file.read(reinterpret_cast<char*>(delta.data()), deltaSize);

        commit.filesDiffs[fname] = std::move(delta);
    }

    return commit;
}

std::vector<std::string> Commit::getChangedFiles() {
    std::vector<std::string> files;
    files.reserve(filesDiffs.size());
    for (const auto& [fname, _] : filesDiffs) {
        files.push_back(fname);
    }
    return files;
}

Commit Commit::fromBytes(const std::vector<uint8_t>& data) {
    Commit commit;
    std::stringstream ss(std::string(reinterpret_cast<const char*>(data.data()), data.size()));
    char magic[8];
    ss.read(magic, 8);
    if (std::memcmp(magic, "COMMIT\0\0", 8) != 0) return commit;

    uint32_t version;
    ss.read(reinterpret_cast<char*>(&version), sizeof(version));
    if (version != 1) return commit;

    auto readString = [&ss]() -> std::string {
        uint32_t len;
        ss.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string str(len, '\0');
        ss.read(&str[0], len);
        return str;
    };

    commit.commitID = readString();
    commit.parentID = readString();
    commit.author = readString();
    commit.date = readString();
    commit.message = readString();

    uint32_t fileCount;
    ss.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));

    for (uint32_t i = 0; i < fileCount; ++i) {
        std::string fname = readString();

        uint32_t deltaSize;
        ss.read(reinterpret_cast<char*>(&deltaSize), sizeof(deltaSize));
        std::vector<uint8_t> delta(deltaSize);
        ss.read(reinterpret_cast<char*>(delta.data()), deltaSize);

        commit.filesDiffs[fname] = std::move(delta);
    }

    return commit;
}
} // namespace UTILS
