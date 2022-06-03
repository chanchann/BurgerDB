#include "MetaCmd.h"
#include <iostream>

int main() {
    std::cout << metaCmdResToStr(MetaCmdRes::COMMAND_SUCCESS) << std::endl;
    std::cout << metaCmdResToStr(MetaCmdRes::COMMAND_UNRECOGNIZED) << std::endl;
}