#include "changecatcher.h"

ChangeCatcher::ChangeCatcher(std::string path, UTILS::VersionsChain chain) : pathToProject(path), currentChain(chain)
{
    //TODO: add checking of path existence if not exist cerr
}
