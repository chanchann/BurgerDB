#include "Cursor.h"
#include "Table.h"
#include "Config.h"
#include "Pager.h"
#include "Status.h"
#include "BTree.h"

#include <string.h>

namespace burgerdb {

Cursor::Cursor(Table *table, uint32_t page_num, uint32_t cell_num) 
    : table_(table),
    page_num_(page_num),
    cell_num_(cell_num) {

}

uint8_t *Cursor::value() {
    uint8_t *page = nullptr;
    int ret = table_->pager()->get(page_num_, &page);
    if(ret != SUCCESS) {
        return nullptr;
    }
    LeafNode leaf_node(page);
    
    return leaf_node.value(cell_num_);
}

void Cursor::next() {
    uint8_t *page = nullptr;
    int ret = table_->pager()->get(page_num_, &page);
    if(ret != SUCCESS) {
        return;
    }
    cell_num_ += 1;
    LeafNode leaf_node(page);
    if(cell_num_ >= (*leaf_node.num_cells())) {
        end_of_table_ = true;
    }
}

int Cursor::insert(uint32_t key, Row *value) {
    uint8_t *page;
    int ret = table_->pager()->get(page_num_, &page);
    if(ret != SUCCESS) {
        return ret;
    }
    LeafNode leaf_node(page);
    uint32_t num_cells = *leaf_node.num_cells();
    if(num_cells >= LEAF_NODE_MAX_CELLS) {
        // Node full
        // TODO : we haven't implement splitting yet
        printf("Need to implement splitting a leaf node.\n");
        exit(EXIT_FAILURE);
    }
    if(cell_num_ < num_cells) {
        // make room for new cell
        for (uint32_t i = num_cells; i > cell_num_; i--) {
            // todo : ??? 
            memcpy(leaf_node.cell(i), leaf_node.cell(i-1), LEAF_NODE_CELL_SIZE);
        }
    }
    leaf_node.increase_num_cells();
    leaf_node.set_key(key, cell_num_);
    value->serialize(leaf_node.value(cell_num_));
    return SUCCESS;
}


} // namespace burgerdb
