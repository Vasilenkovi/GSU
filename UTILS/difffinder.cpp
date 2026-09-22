#include "difffinder.h"
#include "libHDiffPatch/HDiff/diff.h"  // HDiffPatch library

namespace UTILS {

DiffFinder::DiffFinder(std::vector<uint8_t>* ptr_old, std::vector<uint8_t>* ptr_new)
    : oldContent(ptr_old), newContent(ptr_new) {}

std::vector<uint8_t> DiffFinder::findDiff() {
    if (!oldContent || !newContent) {
        return {}; // There will be a Message
    }

    std::vector<unsigned char> out_diff;
    
    // Create compressed diff between old and new data
    // newData first, then oldData (HDiffPatch convention)
    // Using create_single_compressed_diff - recommended approach
    create_single_compressed_diff(
        newContent->data(), newContent->data() + newContent->size(),
        oldContent->data(), oldContent->data() + oldContent->size(),
        out_diff
    );

    // Convert to std::vector<uint8_t>
    return std::vector<uint8_t>(out_diff.begin(), out_diff.end());
}

} // namespace UTILS
