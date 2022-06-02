#ifndef BURGERDB_STATEMENT_H
#define BURGERDB_STATEMENT_H

#include <string>

namespace burgerdb
{

enum class StatementType {
    STATEMENT_INSERT, 
    STATEMENT_SELECT
};

std::string StmtToStr(StatementType stmtType) {
    switch (stmtType) {
    case StatementType::STATEMENT_INSERT: 
        return "STATEMENT_INSERT";
    case StatementType::STATEMENT_SELECT:  
        return "STATEMENT_SELECT";
    default:
        return "UNKNOWN";
    }
}

enum class ExecuteResult {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
};

class Statement {

private:
    StatementType stmtType_;

};
    
} // namespace burgerdb

#endif // BURGERDB_STATEMENT_H