#include "Statement.h"
#include "InputBuffer.h"
#include "Config.h"
#include "Table.h"
#include <string.h>

namespace burgerdb {

Statement::Statement() : row_to_insert_(new Row) {}

Statement::~Statement() {
    delete row_to_insert_;
}

PrepareResult Statement::prepare(const InputBuffer &input) {
    if (strncmp(input.buf, "insert", 6) == 0) {
        return prepare_insert(input);
    }
    if (strcmp(input.buf, "select") == 0) {
        return prepare_select(input);
    }

    return PrepareResult::UNRECOGNIZED_STATEMENT;
}

PrepareResult Statement::prepare_insert(const InputBuffer &input) {
    type_ = StatementType::INSERT;
    char* keyword = strtok(input.buf, " ");
    char* id_string = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");
    if(!id_string || !username || !email) {
        return PrepareResult::SYNTAX_ERROR;
    }

    int id = atoi(id_string);
    if(id < 0) {
        return PrepareResult::NEGATIVE_ID;
    }

    if(strlen(username) > COLUMN_USERNAME_SIZE || strlen(email) > COLUMN_EMAIL_SIZE) {
        return PrepareResult::STRING_TOO_LONG;
    }

    row_to_insert_->id = id;
    strcpy(row_to_insert_->username, username);
    strcpy(row_to_insert_->email, email);

    return PrepareResult::SUCCESS;
}

PrepareResult Statement::prepare_select(const InputBuffer &buffer) {
    type_ = StatementType::SELECT;
    return PrepareResult::SUCCESS;
}

ExecuteResult Statement::execute(const Table &table) {
  switch (type_) {
    case (StatementType::INSERT):
        return execute_insert(table);
    case (StatementType::SELECT):
        return execute_select(table);
  }
}

ExecuteResult execute_insert(const Table &table) {
    if(table.num_rows() >= TABLE_MAX_ROWS) {
        return ExecuteResult::TABLE_FULL;
    }

    return ExecuteResult::SUCCESS;
}

} // namespace burgerdb
