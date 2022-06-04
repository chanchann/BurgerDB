#include "MetaCmd.h"
#include <iostream>

int main() {
    std::cout << metaCmdResToStr(MetaCmdRes::SUCCESS) << std::endl;
    std::cout << metaCmdResToStr(MetaCmdRes::UNRECOGNIZED) << std::endl;
}