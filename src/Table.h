#ifndef BURGERDB_TABLE_H
#define BURGERDB_TABLE_H

#include <cstdint>

namespace burgerdb {

class Pager;

class Table {
    
private:
    Pager *pager;
    uint32_t num_rows;
};
    
} // namespace burgerdb


#endif // BURGERDB_TABLE_H