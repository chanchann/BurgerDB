#include "Interface.h"
#include "MetaCmd.h"

Interface::Interface() {
}

void Interface::printPrompt() {
    std::cout << "BurgerDB > ";
}

void Interface::printInfo() {
    std::cout << "BurgerDB version 0.1.0" << std::endl;
    std::cout << "Enter \".help\" for usage hints." << std::endl;
    std::cout << "Connected to a transient in-memory database." << std::endl;
    std::cout << "Use \".open FILENAME\" to reopen on a persistent database." << std::endl;
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









