#include "BTree.h"
#include "Row.h"
#include "Config.h"

namespace burgerdb {

LeafNode::LeafNode(uint8_t *node) 
    : node_(node) {
}   

void LeafNode::init() {
    *num_cells() = 0;
}

uint32_t *LeafNode::num_cells() {
    // todo : can't use static_cast here
    return reinterpret_cast<uint32_t *>(node_ + LEAF_NODE_NUM_CELLS_OFFSET);
}

void LeafNode::increase_num_cells() {
    *(this->num_cells()) += 1;
}

uint8_t *LeafNode::cell(uint32_t cell_num) {
    return node_ + LEAF_NODE_HEADER_SIZE + cell_num * LEAF_NODE_CELL_SIZE;
}

uint8_t *LeafNode::key(uint32_t cell_num) {
    return this->cell(cell_num);
}

void LeafNode::set_key(uint32_t key, uint32_t cell_num) {
    *reinterpret_cast<uint32_t *>(this->key(cell_num)) = key;
}

uint8_t *LeafNode::value(uint32_t cell_num) {
    return this->cell(cell_num) + LEAF_NODE_KEY_SIZE;
}

void LeafNode::print() {
    uint32_t num_cells = *this->num_cells();
    fprintf(stderr, "leaf (size %d)\n");
    for (uint32_t i = 0; i < num_cells; i++) {
        uint32_t key = *this->key(i);
        fprintf(stderr, "  - %d : %dn\n", i, key);
    }
}


} // namespace burgerdb
