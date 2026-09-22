#include "dirUtils.h"
#include <filesystem>
#include <fstream>

namespace UTILS {

Message dirUtils::checkFiles(const std::vector<std::string>& files, 
                            const std::string& caller, 
                            const std::string& directory, 
                            int defaultStatus) {
    Message msg(caller, "dirUtils", "CHECK_FILES");
    bool allExist = true;
    
    for (const auto& filename : files) {
        std::filesystem::path filepath = std::filesystem::path(directory) / filename;
        if (!std::filesystem::exists(filepath)) {
            msg.setStatus(statusMaps::WARNING);
            msg.setDetails("File not found: " + filepath.string());
            allExist = false;
        }
    }
    
    if (allExist) {
        msg.setStatus(defaultStatus);
    }
    msg.setBooleanStatus(allExist);
    return msg;
}

} // namespace UTILS
