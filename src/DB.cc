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
    uint32_t num_full_pages = table_->num_rows() / ROWS_PER_PAGE;
    for (uint32_t i = 0; i < num_full_pages; i++) {
        if (pager_->pages(i) == nullptr) {
            continue;
        }
        pager_->flush(i, PAGE_SIZE);
        pager_->free(i);
    }
    // There may be a partial page to write to the end of the file
    // todo : This should not be needed after we switch to a B-tree
    uint32_t num_additional_rows = table_->num_rows() % ROWS_PER_PAGE;
    if(num_additional_rows > 0) {
        uint32_t page_num = num_full_pages;
        if(pager_->pages(page_num) != nullptr) {
            pager_->flush(page_num, num_additional_rows * ROW_SIZE);
            pager_->free(page_num);
        }
    }
    pager_->close();
}

int DB::start_client() {
    db_client_->start();
    return SUCCESS;
}

} // namespace burgerdb
