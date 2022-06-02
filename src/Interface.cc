#include "Interface.h"
#include "MetaCmd.h"
#include <cstdio>

namespace burgerdb {

void Interface::printPrompt() {
    fprintf(stderr, "BurgerDB > ");
}

void Interface::printInfo() {
    fprintf(stderr, "BurgerDB version 0.1.0\n");
    fprintf(stderr, "Enter \".help\" for usage hints.\n");
    fprintf(stderr, "Connected to a transient in-memory database.\n");
    fprintf(stderr, "Use \".open FILENAME\" to reopen on a persistent database.\n");
}

void Interface::start() {
    printInfo();
    while(true) {
        std::string cmd;
        printPrompt();
        std::getline(std::cin, cmd);
        if(!cmd.empty() && cmd[0] == '.') {
            switch(MetaCmd::execute(cmd)) {
            case MetaCmdRes::META_COMMAND_SUCCESS:
                continue;
            case MetaCmdRes::META_COMMAND_UNRECOGNIZED:
                std::cout << "Unrecognized command : " << cmd << std::endl; 
                continue;
            }
        }
        
    }
}

} // namespace burgerdb











