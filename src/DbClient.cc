#include "DbClient.h"
#include "MetaCmd.h"
#include "Status.h"
#include "Statement.h"
#include "Table.h"
#include "DB.h"
#include <cstdio>

namespace burgerdb {

DbClient::DbClient(DB *db)
    : db_(db),
    running_(false) {
}

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
    running_ = true;
    while(running_) {
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
            case MetaCmdRes::SUCCESS:
                continue;
            case MetaCmdRes::UNRECOGNIZED:
                fprintf(stderr, "Unrecognized command '%s'\n", input_buffer_.buf);
                continue;
            }
        }

        // statement
        Statement statement;
        switch (statement.prepare(input_buffer_)) {
            case (PrepareResult::SUCCESS):
                break;
            case (PrepareResult::NEGATIVE_ID):
                fprintf(stderr, "ID must be positive.\n");
                continue;
            case (PrepareResult::STRING_TOO_LONG):
                fprintf(stderr, "String is too long.\n");
                continue;
            case (PrepareResult::SYNTAX_ERROR):
                fprintf(stderr, "Syntax error. Could not parse statement.\n");
                continue;
            case (PrepareResult::UNRECOGNIZED_STATEMENT):
                fprintf(stderr, "Unrecognized keyword at start of '%s'.\n",
                    input_buffer_.buf);
                continue;
        }

        switch (statement.execute(db_->table())) {
            case (ExecuteResult::SUCCESS):
                fprintf(stderr, "Executed.\n");
                break;
            case (ExecuteResult::TABLE_FULL):
                fprintf(stderr, "Error: Table full.\n");
                break;
            default:
                fprintf(stderr, "Error: Unknown execute type.\n");
                break;
        }
    }
}

void DbClient::stop() {
    running_ = false;
    fprintf(stderr, "Good bye.");
}

} // namespace burgerdb











