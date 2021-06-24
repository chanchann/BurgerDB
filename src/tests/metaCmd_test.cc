#include "MetaCmd.h"
#include <iostream>

int main() {
    std::cout << metaCmdResToStr(MetaCmdRes::META_COMMAND_SUCCESS) << std::endl;
    std::cout << metaCmdResToStr(MetaCmdRes::META_COMMAND_UNRECOGNIZED) << std::endl;
}