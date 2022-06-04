#include "DB.h"
#include "Table.h"
#include "Status.h"
#include "DbClient.h"

namespace burgerdb {

DB::DB() : table_(new Table),
        db_client_(new DbClient(this)) {
}

DB::~DB() {
    delete table_;
    delete db_client_;
}

int DB::open(const std::string &file_name) {
    return table_->init(file_name);
}

int DB::close() {
    // todo : here we deinit to flush then stop client
    int ret = table_->deinit();
    this->stop_client();
    return ret;
}

int DB::start_client() {
    db_client_->start();
    return SUCCESS;
}

int DB::stop_client() {
    db_client_->stop();
    return SUCCESS;
}

Table *DB::table() const { return table_; }

} // namespace burgerdb
