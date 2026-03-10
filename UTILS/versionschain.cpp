#include "versionschain.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <deque>
#include <algorithm>
extern "C" {
    #include "xdelta3.h"
}

namespace UTILS {

static std::string branchDirFromChainPath(const std::string& chainPath) {
    return std::filesystem::path(chainPath).parent_path().string();
}

std::string VersionsChain::branchPath() const {
    return branchDirFromChainPath(HEAD_PATH);
}

std::string VersionsChain::commitsDir() const {
    return branchPath() + "/commits";
}

std::pair<std::string, std::string> VersionsChain::readHeadTail() const {
    std::ifstream file(HEAD_PATH);
    std::string head, tail;
    if (file.is_open()) {
        std::getline(file, head);
        std::getline(file, tail);
    }
    return {head, tail};
}

bool VersionsChain::writeHeadTail(const std::string& head, const std::string& tail) const {
    std::ofstream file(HEAD_PATH, std::ios::trunc);
    if (!file.is_open()) return false;
    file << head << std::endl;
    file << tail << std::endl;
    return true;
}

std::pair<Message, Commit> VersionsChain::loadCommit(const std::string& hash) const {
    Message msg("loadCommit", "VersionsChain", "LOAD_COMMIT");
    std::string commitPath = commitsDir() + "/" + hash + ".commit";
    std::ifstream file(commitPath, std::ios::binary);
    if (!file.is_open()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Commit file not found: " + commitPath);
        return {msg, Commit()};
    }
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(size);
    if (!file.read(reinterpret_cast<char*>(data.data()), size)) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Failed to read commit file");
        return {msg, Commit()};
    }
    Commit commit = Commit::fromBytes(data);
    if (commit.getID().empty()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Failed to parse commit data");
        return {msg, Commit()};
    }
    msg.setStatus(statusMaps::STATUS_OK);
    msg.setBooleanStatus(true);
    return {msg, std::move(commit)};
}

VersionsChain::VersionsChain(std::string pathToChainHeader)
    : HEAD_PATH(std::move(pathToChainHeader))
{
    TAIL_PATH = "";
    std::filesystem::create_directories(commitsDir());
    if (!std::filesystem::exists(HEAD_PATH)) {
        std::ofstream(HEAD_PATH);
    }
}

Message VersionsChain::newHead(std::string commitID) {
    Message msg("VersionsChain::newHead", "VersionsChain", "NEW_HEAD");
    if (commitID.empty()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Commit ID is empty");
        return msg;
    }
    auto [head, tail] = readHeadTail();
    if (!writeHeadTail(commitID, tail.empty() ? commitID : tail)) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Failed to write versionchain file");
        return msg;
    }
    msg.setStatus(statusMaps::STATUS_OK);
    msg.setBooleanStatus(true);
    msg.setDetails("New HEAD set to " + commitID);
    return msg;
}

std::pair<Message, std::vector<uint8_t>> VersionsChain::getVersion(std::string commitID) {
    Message msg("VersionsChain::getVersion", "VersionsChain", "GET_VERSION");
    std::vector<uint8_t> data;
    if (commitID.empty()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Commit ID is empty");
        return {msg, data};
    }
    std::string commitPath = commitsDir() + "/" + commitID + ".commit";
    std::ifstream file(commitPath, std::ios::binary);
    if (!file.is_open()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Commit file not found: " + commitPath);
        return {msg, data};
    }
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    data.resize(size);
    if (!file.read(reinterpret_cast<char*>(data.data()), size)) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Failed to read commit file");
        return {msg, data};
    }
    msg.setStatus(statusMaps::STATUS_OK);
    msg.setBooleanStatus(true);
    return {msg, data};
}

std::pair<Message, std::vector<uint8_t>> VersionsChain::getHeadVersion() {
    Message msg("VersionsChain::getHeadVersion", "VersionsChain", "GET_HEAD");
    auto [head, tail] = readHeadTail();
    if (head.empty()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("No commits (HEAD empty)");
        return {msg, {}};
    }
    return getVersion(head);
}

Message VersionsChain::restoreCommit(std::string commitID, const std::string& projectPath) {
    Message msg("VersionsChain::restoreCommit", "VersionsChain", "RESTORE_COMMIT");
    if (commitID.empty()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Commit ID is empty");
        return msg;
    }
    if (!std::filesystem::exists(projectPath)) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Project path does not exist");
        return msg;
    }

    auto [head, tail] = readHeadTail();
    if (tail.empty()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("No commits in branch (tail empty)");
        return msg;
    }

    // Строим цепочку от HEAD до TAIL, затем переворачиваем
    std::deque<std::string> reverseChain;
    std::string current = head;
    while (!current.empty()) {
        reverseChain.push_front(current);
        if (current == tail) break;
        auto [loadMsg, commit] = loadCommit(current);
        if (loadMsg.getStatusCode() != statusMaps::STATUS_OK) {
            return loadMsg;
        }
        current = commit.getParentID();
    }

    // Выбираем коммиты до целевого включительно
    std::vector<std::string> targetChain;
    bool found = false;
    for (const auto& hash : reverseChain) {
        targetChain.push_back(hash);
        if (hash == commitID) {
            found = true;
            break;
        }
    }
    if (!found) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Commit not found in branch");
        return msg;
    }

    // Очищаем рабочую директорию, но сохраняем скрытые файлы
    // (потом поменяю добавив что то типо gitignore чтобы защищать не отслеживаемые файлы)
    for (const auto& entry : std::filesystem::directory_iterator(projectPath)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (!filename.empty() && filename[0] == '.') {
                continue;
            }
            std::filesystem::remove(entry.path());
        }
    }

    // Применяем коммиты по порядку
    for (const auto& hash : targetChain) {
        auto [loadMsg, commit] = loadCommit(hash);
        if (loadMsg.getStatusCode() != statusMaps::STATUS_OK) {
            return loadMsg;
        }
        for (const auto& [fname, delta] : commit.getFilesDiffs()) {
            std::string filePath = projectPath + "/" + fname;
            if (commit.getParentID().empty()) {
                // Первый коммит: полный файл
                std::ofstream outFile(filePath, std::ios::binary);
                outFile.write(reinterpret_cast<const char*>(delta.data()), delta.size());
            } else {
                // Применяем дельту к существующему файлу
                std::vector<uint8_t> oldData;
                if (std::filesystem::exists(filePath)) {
                    std::ifstream inFile(filePath, std::ios::binary | std::ios::ate);
                    size_t size = inFile.tellg();
                    inFile.seekg(0);
                    oldData.resize(size);
                    inFile.read(reinterpret_cast<char*>(oldData.data()), size);
                }
                std::vector<uint8_t> newData;
                newData.resize(oldData.size() + delta.size() + 1024);
                size_t newSize = newData.size();
                int ret = xd3_decode_memory(
                    delta.data(), delta.size(),
                    oldData.data(), oldData.size(),
                    newData.data(), &newSize,
                    newData.size(), 0);
                if (ret != 0) {
                    msg.setStatus(statusMaps::FAILURE);
                    msg.setReason("Failed to apply delta for " + fname);
                    return msg;
                }
                newData.resize(newSize);
                std::ofstream outFile(filePath, std::ios::binary);
                outFile.write(reinterpret_cast<const char*>(newData.data()), newData.size());
            }
        }
    }

    msg.setStatus(statusMaps::STATUS_OK);
    msg.setBooleanStatus(true);
    msg.setDetails("Restored to commit " + commitID);
    return msg;
}

Message VersionsChain::removeVersion(std::string commitID) {
    Message msg("VersionsChain::removeVersion", "VersionsChain", "REMOVE_VERSION");
    if (commitID.empty()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Commit ID is empty");
        return msg;
    }

    auto [head, tail] = readHeadTail();
    if (head.empty()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("No commits in branch");
        return msg;
    }

    // Строим цепочку от HEAD до TAIL (в порядке от HEAD к TAIL)
    std::deque<std::string> chain;
    std::string current = head;
    while (!current.empty()) {
        chain.push_back(current);
        if (current == tail) break;
        auto [loadMsg, commit] = loadCommit(current);
        if (loadMsg.getStatusCode() != statusMaps::STATUS_OK) {
            return loadMsg;
        }
        current = commit.getParentID();
    }

    auto it = std::find(chain.begin(), chain.end(), commitID);
    if (it == chain.end()) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Commit not found in branch");
        return msg;
    }
    size_t index = std::distance(chain.begin(), it); // индекс от HEAD

    // Удаляем коммиты от HEAD до удаляемого включительно
    for (size_t j = 0; j <= index; ++j) {
        std::string hash = chain[j];
        std::string commitPath = commitsDir() + "/" + hash + ".commit";
        std::filesystem::remove(commitPath);
    }

    // Новый HEAD — следующий после удалённого (если есть), иначе пусто
    std::string newHead = (index + 1 < chain.size()) ? chain[index + 1] : "";
    // Новый TAIL — последний из оставшихся (если остались), иначе пусто
    std::string newTail = (index < chain.size() - 1) ? chain.back() : "";

    if (!writeHeadTail(newHead, newTail)) {
        msg.setStatus(statusMaps::FAILURE);
        msg.setReason("Failed to update versionchain");
        return msg;
    }

    msg.setStatus(statusMaps::STATUS_OK);
    msg.setBooleanStatus(true);
    msg.setDetails("Removed commits from HEAD to " + commitID + ", new HEAD = " + newHead);
    return msg;
}

} // namespace UTILS
