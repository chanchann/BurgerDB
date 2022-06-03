#ifndef BURGERDB_TABLE_H
#define BURGERDB_TABLE_H

#include <cstdint>
#include "Noncopyable.h"

namespace burgerdb {

class Cursor;
class Pager;

class Table : public Noncopyable {
public:
    Table();

    ~Table();

    int init(const std::string &file_name);

    int deinit();

    Cursor *start();

    Cursor *end();

    Pager *pager() const { return pager_; }

    uint32_t num_rows() const { return num_rows_; }

    void set_num_rows(uint32_t num_rows) { num_rows_ = num_rows; }

private:
    uint32_t num_rows_ = 0;
    Pager *pager_;
};
    
} // namespace burgerdb


#endif // BURGERDB_TABLE_H