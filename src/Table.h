#ifndef BURGERDB_TABLE_H
#define BURGERDB_TABLE_H

#include <cstdint>
#include "Noncopyable.h"

namespace burgerdb {

class Table : public Noncopyable {
public:
    Table() = default;

    ~Table() = default;

    uint32_t num_rows() { return num_rows_; }

    void set_num_rows(uint32_t num_rows) { num_rows_ = num_rows; }

private:
    uint32_t num_rows_;
};
    
} // namespace burgerdb


#endif // BURGERDB_TABLE_H