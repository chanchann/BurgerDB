#include <string>

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
