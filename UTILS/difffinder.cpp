#include "difffinder.h"
extern "C" {
    #include "xdelta3.h"
}
#include <vector>

namespace UTILS {

DiffFinder::DiffFinder(std::vector<uint8_t>* ptr_old, std::vector<uint8_t>* ptr_new)
    : oldContent(ptr_old), newContent(ptr_new) {}

std::vector<uint8_t> DiffFinder::findDiff() {
    if (!oldContent || !newContent) {
        return {}; // There will be a Message
    }

    size_t old_size = oldContent->size();
    size_t new_size = newContent->size();

    // Maybe later i'll do some trickery with dynamic memory allocation if i ever fell risky
    std::vector<uint8_t> delta;
    delta.resize(old_size + new_size + 1024);
    size_t delta_size = delta.size();

    int ret = xd3_encode_memory(
        newContent->data(), new_size,
        oldContent->data(), old_size,
        delta.data(), &delta_size,
        delta.size(), 0);

    if (ret != 0) {
        // There will be a Message
        return {};
    }

    delta.resize(delta_size);
    return delta;
}

} // namespace UTILS
