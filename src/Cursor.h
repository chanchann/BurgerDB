#ifndef BURGERDB_CURSOR_H
#define BURGERDB_CURSOR_H

#include <stdint.h>

namespace burgerdb {

class Table;

// Cursor represents a location in the table
class Cursor {
public:
    Cursor(Table *table, uint32_t row_num);

    // Returns a pointer to the position described by the cursor
    void *value();

    void next();

    void set_end_of_table(bool end_of_table) { end_of_table_ = end_of_table; }
private: 
    Table *table_;
    uint32_t row_num_;
    bool end_of_table_;     // Indicates a position one past the last element
};


} // namespace burgerdb


#endif // BURGERDB_TABLE_H