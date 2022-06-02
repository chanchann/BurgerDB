#ifndef BURGERDB_DB_H
#define BURGERDB_DB_H

#include <string>
#include "Noncopyable.h"

namespace burgerdb {

class Table;

class DB : public Noncopyable {
public:
    DB() = default;

    // todo : status
    void open(std::string &&file_name);

private:
    Table *table_ = nullptr;
};

} // namespace burgerdb


#endif // BURGERDB_DB_H