#include "DB.h"
#include "Table.h"
#include "Pager.h"
#include "Status.h"
#include "DbClient.h"

namespace burgerdb {

DB::DB() : pager_(new Pager), 
        table_(new Table),
        db_client_(new DbClient) {
}

DB::~DB() {
    delete pager_;
    delete table_;
    delete db_client_;
}

int DB::open(const std::string &file_name) {
    pager_->init(file_name);
    uint32_t num_rows = pager_->file_len() / ROW_SIZE;
    table_->set_num_rows(num_rows);
    // table->pager = pager;
    return SUCCESS;
}

int DB::close() {

}

int DB::start_client() {
    db_client_->start();
    return SUCCESS;
}

} // namespace burgerdb
