#ifndef BURGERDB_DB_H
#define BURGERDB_DB_H

#include <string>
#include "Noncopyable.h"

namespace burgerdb {

class Table;
class DbClient;

class DB : public Noncopyable {
public:
    DB();

    ~DB();

    int open(const std::string &file_name);

    // 1. flushes the page cache to disk
    // 2. closes the database file
    int close();

    int start_client();

    int stop_client();
    
    Table *table() const;

private:
    Table *table_;
    DbClient *db_client_;
};

} // namespace burgerdb


#endif // BURGERDB_DB_H