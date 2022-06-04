#include "Table.h"
#include "Cursor.h"
#include "Pager.h"
#include "Status.h"

namespace burgerdb {

Table::Table()
    : num_rows_(0),
    pager_(new Pager){
}

Table::~Table() {
    delete pager_;
}

int Table::init(const std::string &file_name) {
    int ret = pager_->init(file_name);
    if(ret == SUCCESS) {
        num_rows_ = pager_->file_len() / ROW_SIZE;
    }
    return ret;
}

int Table::deinit() {
    uint32_t num_full_pages = num_rows_ / ROWS_PER_PAGE;
    for (uint32_t i = 0; i < num_full_pages; i++) {
        if (pager_->pages(i) == nullptr) {
            continue;
        }
        pager_->flush(i, PAGE_SIZE);
        pager_->free(i);
    }
    // There may be a partial page to write to the end of the file
    // todo : This should not be needed after we switch to a B-tree
    uint32_t num_additional_rows = num_rows_ % ROWS_PER_PAGE;
    if(num_additional_rows > 0) {
        uint32_t page_num = num_full_pages;
        if(pager_->pages(page_num) != nullptr) {
            pager_->flush(page_num, num_additional_rows * ROW_SIZE);
            pager_->free(page_num);
        }
    }
    pager_->close();
    return SUCCESS;
}

Cursor *Table::start() {
    auto *cursor = new Cursor(this, 0);
    cursor->set_end_of_table(num_rows_ == 0);
    return cursor;
}

Cursor *Table::end() {
    auto *cursor = new Cursor(this, num_rows_);
    cursor->set_end_of_table(true);
    return cursor;
}

} // namespace burgerdb
