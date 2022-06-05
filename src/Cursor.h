#ifndef BURGERDB_CURSOR_H
#define BURGERDB_CURSOR_H

#include <stdint.h>
#include "Noncopyable.h"

namespace burgerdb {

class Table;

// Cursor represents a location in the table
class Cursor : public Noncopyable {
public:
    Cursor(Table *table, uint32_t page_num, uint32_t cell_num);

    // Returns a pointer to the position described by the cursor
    uint8_t *value();

    void next();

    void set_end_of_table(bool end_of_table) { end_of_table_ = end_of_table; }

    bool end_of_table() { return end_of_table_; }

    int insert(uint32_t key, Row *value);

private: 
    Table *table_;
    uint32_t page_num_;
    uint32_t cell_num_;
    bool end_of_table_;     // Indicates a position one past the last element
};


} // namespace burgerdb


#endif // BURGERDB_TABLE_H