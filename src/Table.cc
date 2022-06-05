#include "Table.h"
#include "Cursor.h"
#include "Pager.h"
#include "Status.h"
#include "BTree.h"

namespace burgerdb {

Table::Table()
    : root_page_num_(0),
    pager_(new Pager){
}

Table::~Table() {
    delete pager_;
}

int Table::init(const std::string &file_name) {
    int ret = pager_->init(file_name);
    if(ret != SUCCESS) {
        return ret;
    }

    root_page_num_ = 0;
    if(pager_->num_pages_ == 0) {
        // New database file. Initialize page 0 as leaf node.
        uint8_t *page;
        ret = pager_->get(0, &page);
        if(ret != SUCCESS) {
            return ret;
        }
        LeafNode leaf_node(page);
        leaf_node.init();
    }

    return ret;
}

int Table::deinit() {
    for (uint32_t i = 0; i < pager_->num_pages(); i++) {
        if (pager_->pages(i) == nullptr) {
            continue;
        }
        pager_->flush(i);
        pager_->free(i);
    }

    return pager_->close();
}

Cursor *Table::start() {
    uint8_t *root_node;
    int ret = pager_->get(root_page_num_, &root_node);
    if(ret != SUCCESS) {
        return nullptr;
    }
    LeafNode leaf_node(root_node);
    uint32_t num_cells = *leaf_node.num_cells();

    auto *cursor = new Cursor(this, root_page_num_, 0);
    cursor->set_end_of_table(num_cells == 0);

    return cursor;
}

Cursor *Table::end() {
    uint8_t *root_node;
    int ret = pager_->get(root_page_num_, &root_node);
    if(ret != SUCCESS) {
        return nullptr;
    }
    LeafNode leaf_node(root_node);
    uint32_t num_cells = *leaf_node.num_cells();

    auto *cursor = new Cursor(this, root_page_num_, num_cells);
    cursor->set_end_of_table(true);

    return cursor;
}

} // namespace burgerdb
