#include "DbClient.h"
#include "MetaCmd.h"
#include "Status.h"
#include "Statement.h"
#include <cstdio>

namespace burgerdb {

void DbClient::printPrompt() {
    fprintf(stderr, "BurgerDB > ");
}

void DbClient::printInfo() {
    fprintf(stderr, "BurgerDB version 0.1.0\n");
    fprintf(stderr, "Enter \".help\" for usage hints.\n");
    fprintf(stderr, "Connected to a transient in-memory database.\n");
    fprintf(stderr, "Use \".open FILENAME\" to reopen on a persistent database.\n");
}

void DbClient::start() {
    printInfo();
    while(true) {
        printPrompt();
        int ret = input_buffer_.read();
        if(ret != SUCCESS) {
            fprintf(stderr, "Error reading input\n");
            continue;
        }
        // meta
        // we must have at least one char in buf('\0')
        if(input_buffer_.buf[0] == '.') {
            switch(MetaCmd::execute(input_buffer_, db_)) {
            case MetaCmdRes::COMMAND_SUCCESS:
                continue;
            case MetaCmdRes::COMMAND_UNRECOGNIZED:
                fprintf(stderr, "Unrecognized command '%s'\n", input_buffer_.buf);
                continue;
            }
        }

        // statement
        Statement statement;

    }
}

} // namespace burgerdb











