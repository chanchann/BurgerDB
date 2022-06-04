#include "Cursor.h"
#include "Table.h"
#include "Config.h"
#include "Pager.h"
#include "Status.h"

namespace burgerdb {

Cursor::Cursor(Table *table, uint32_t row_num)
    : table_(new Table),
    row_num_(row_num) {
}

uint8_t *Cursor::value() {
    uint32_t page_num = row_num_ / ROWS_PER_PAGE;
    Pager *pager = table_->pager();
    uint8_t *page = nullptr;
    int ret = pager->get(page_num, &page);
    if(ret != SUCCESS) {
        return nullptr;
    }
    uint32_t row_offset = row_num_ % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}

void Cursor::next() {
    row_num_ += 1;
    if(row_num_ >= table_->num_rows()) {
        end_of_table_ = true;
    }
}

} // namespace burgerdb
