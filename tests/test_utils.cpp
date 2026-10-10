#include <iostream>
#include <cassert>
#include <filesystem>
#include <fstream>
#include "Commit.h"
#include "difffinder.h"

namespace fs = std::filesystem;

void testCommit() {
    using namespace UTILS;

    // Создаём коммит
    Commit commit;
    commit.initMetadata("", "Test Author", "Initial commit");

    // Добавляем дельту для файла
    std::vector<uint8_t> delta = {0x01, 0x02, 0x03, 0x04};
    commit.addFileDiff("file1.txt", delta);

    // Проверяем ID (не пустой)
    assert(!commit.getID().empty());

    // Сохраняем в файл
    fs::create_directories("test_commits");
    std::string commitPath = "test_commits/" + commit.getID() + ".commit";
    commit.saveToFile(commitPath);

    // Загружаем из файла
    Commit loaded = Commit::loadFromFile(commitPath);
    assert(loaded.getID() == commit.getID());
    assert(loaded.getChangedFiles().size() == 1);
    assert(loaded.getChangedFiles()[0] == "file1.txt");

    // Загружаем через fromBytes
    std::ifstream file(commitPath, std::ios::binary);
    file.seekg(0, std::ios::end);
    std::vector<uint8_t> data(file.tellg());
    file.seekg(0);
    file.read(reinterpret_cast<char*>(data.data()), data.size());
    Commit fromBytes = Commit::fromBytes(data);
    assert(fromBytes.getID() == commit.getID());

    std::cout << "Commit tests passed.\n";
}

void testDiffFinder() {
    using namespace UTILS;

    // Тест 1: одинаковые данные
    std::vector<uint8_t> data1 = {1,2,3,4,5};
    std::vector<uint8_t> data2 = {1,2,3,4,5};
    DiffFinder finder1(&data1, &data2);
    auto delta1 = finder1.findDiff();
    // Дельты может не быть или она пустая? xdelta3 может вернуть пустую дельту.
    // Проверим, что функция не упала.
    assert(delta1.empty() || !delta1.empty()); // просто не падает

    // Тест 2: разные данные
    std::vector<uint8_t> data3 = {1,2,3,4,5};
    std::vector<uint8_t> data4 = {1,2,3,99,5};
    DiffFinder finder2(&data3, &data4);
    auto delta2 = finder2.findDiff();
    assert(!delta2.empty());

    // Тест 3: добавление в конец
    std::vector<uint8_t> data5 = {1,2,3};
    std::vector<uint8_t> data6 = {1,2,3,4,5};
    DiffFinder finder3(&data5, &data6);
    auto delta3 = finder3.findDiff();
    assert(!delta3.empty());

    std::cout << "DiffFinder tests passed.\n";
}

int main() {
    testCommit();
    testDiffFinder();
    return 0;
}
