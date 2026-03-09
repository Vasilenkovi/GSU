#ifndef DIFFFINDER_H
#define DIFFFINDER_H
#include <xdelta3.h>
#include "Message.h"
#include <vector>
#include <stdint.h>
namespace UTILS {

    class DiffFinder
    {
    private:
        std::vector<uint8_t>* oldContent;
        std::vector<uint8_t>* newContent;
    public:
        DiffFinder(std::vector<uint8_t>* ptr_old, std::vector<uint8_t>* ptr_new);
        //all data will be transformed in bytes
        std::vector<uint8_t> findDiff();
    };
}
#endif // DIFFFINDER_H
