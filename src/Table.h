#ifndef BURGERDB_TABLE_H
#define BURGERDB_TABLE_H

#include <cstdint>
#include <string>
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

    uint32_t root_page_num() { return root_page_num_; }
private:
    uint32_t root_page_num_;
    Pager *pager_;
};
    
} // namespace burgerdb


#endif // BURGERDB_TABLE_H