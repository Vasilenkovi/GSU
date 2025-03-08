#include "repository-keeper/headers/repository.h"



RepositoryFile::RepositoryFile(std::string filename, std::string path, std::string coreVCSpath) {
    this->filename = filename;
    this->path = path;
    this->coreVCSpath = coreVCSpath;
}
