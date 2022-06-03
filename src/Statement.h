#ifndef BURGERDB_STATEMENT_H
#define BURGERDB_STATEMENT_H

#include <string>

namespace burgerdb {

enum class StatementType {
    INSERT, 
    SELECT,
    UNKNOWN
};

enum class ExecuteResult {
    SUCCESS,
    TABLE_FULL
};

enum class PrepareResult {
    SUCCESS,
    NEGATIVE_ID,
    STRING_TOO_LONG,
    SYNTAX_ERROR,
    UNRECOGNIZED_STATEMENT
};

class Row;
class Table;
class InputBuffer;

class Statement {
    Statement();

    ~Statement();

    ExecuteResult execute(const Table &table);

    PrepareResult prepare(const InputBuffer &buffer);

private:
    PrepareResult prepare_insert(const InputBuffer &buffer);

    PrepareResult prepare_select(const InputBuffer &buffer);

    ExecuteResult execute_insert(const Table &table);

    ExecuteResult execute_select(const Table &table);
private:
    StatementType type_;
    Row *row_to_insert_;            // only used by insert statement
};
    
} // namespace burgerdb

#endif // BURGERDB_STATEMENT_H