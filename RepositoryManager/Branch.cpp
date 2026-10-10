#include "Branch.h"

Branch::Branch() : branchName(""), BRANCH_HEAD("") {
    // Default constructor
}

Branch::Branch(const std::string& name) : branchName(name), BRANCH_HEAD("") {
    // Constructor with name
}
