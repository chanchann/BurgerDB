#ifndef BURGERDB_BTREE_H
#define BURGERDB_BTREE_H

#include <stdint.h>
#include <string>

namespace burgerdb {

enum class NodeType {
    INTERNAL,
    LEAF
};

class Row;

class LeafNode {
public:
    LeafNode(uint8_t *node);

    void init();

    uint32_t *num_cells();

    void increase_num_cells(); 

    uint8_t *cell(uint32_t cell_num);

    uint8_t *key(uint32_t cell_num);

    void set_key(uint32_t key, uint32_t cell_num);

    uint8_t *value(uint32_t cell_num);

    void print();

private:
    uint8_t *node_;
};


} // namespace burgerdb


#endif // BURGERDB_BTREE_H