#include "DB.h"
#include "Table.h"
#include "Pager.h"
#include "Status.h"
#include "DbClient.h"

namespace burgerdb {

DB::DB() : table_(new Table),
        db_client_(new DbClient) {
}

DB::~DB() {
    delete table_;
    delete db_client_;
}

int DB::open(const std::string &file_name) {
    return table_->init(file_name);
}

int DB::close() {
    return table_->deinit();
}

int DB::start_client() {
    db_client_->start();
    return SUCCESS;
}

} // namespace burgerdb
