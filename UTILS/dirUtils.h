#ifndef DIRUTILS_H
#define DIRUTILS_H

#include "Message.h"
#include <string>
#include <vector>

namespace UTILS {

class dirUtils {
public:
    // Checks if all files in the list exist in the specified directory
    static Message checkFiles(const std::vector<std::string>& files, 
                              const std::string& caller, 
                              const std::string& directory, 
                              int defaultStatus = statusMaps::STATUS_OK);
};

} // namespace UTILS

#endif // DIRUTILS_H
