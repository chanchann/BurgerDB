#ifndef BURGERDB_DBCLIENT_H
#define BURGERDB_DBCLIENT_H

#include "InputBuffer.h"

namespace burgerdb {

class DB;

class DbClient {
public:
    DbClient() = default;

    void start();

    // void stop();

private:
    void printPrompt();
    
    void printInfo();
    
private:
    InputBuffer input_buffer_;
    DB *db_;
};
    
} // namespace burgerdb

#endif // BURGERDB_DBCLIENT_H