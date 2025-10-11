#include "UTILS/headers/Message.h"
#include <filesystem>
#include <QDir>
#include <string>
#include <vector>

namespace dirUtils
{

std::string getCurrentPath()
{
    return QDir::currentPath().toStdString();
}

Message checkFiles(std::vector<std::string> files, std::string Producer, std::string checkDir, int statusOnFail)
{
    /*
     * checks if <files> exists in <checkDir> and creates <Message>
    */
    Message msg("checkFiles", Producer);
    for (const auto& filename : files)
    {
        std::filesystem::path filePath = std::filesystem::path(checkDir) / filename;

        if (!std::filesystem::exists(filePath))
        {
            msg.setStatus(statusOnFail);

            // Append missing file info to Details
            std::string currentDetails = msg.getDict()["Details"];
            if (!currentDetails.empty())
                currentDetails += "; ";
            currentDetails += filename + " not found";
            msg.setDetails(currentDetails);
            msg.setReason("Missing required file(s)");
            msg.setBooleanStatus(false);
        }
    }
    return msg;
}
}
