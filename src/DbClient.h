#ifndef BURGERDB_DBCLIENT_H
#define BURGERDB_DBCLIENT_H

#include "InputBuffer.h"
#include "Noncopyable.h"

namespace burgerdb {

class DB;

class DbClient : public Noncopyable {
public:
    DbClient(DB *db);

    ~DbClient() = default;

    void start();

    void stop();

private:
    void printPrompt();
    
    void printInfo();
    
private:
    InputBuffer input_buffer_;
    DB *db_;
    bool running_ = false;
};
    
} // namespace burgerdb

#endif // BURGERDB_DBCLIENT_H