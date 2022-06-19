#ifndef BURGERDB_BTREE_H
#define BURGERDB_BTREE_H

#include <stdint.h>
#include <string>
#include <vector>
#include <mutex>

namespace burgerdb 
{

enum class BTreePageType 
{
    INVALID_PAGE_TYPE = 0,
    LEAF_PAGE,
    INTERNAL_PAGE
};


// page layout
// ---------------------------------------------------------------------
// | page_type (4) | log_seq_num (4) | current_size (4) | max_size (4) |
// ---------------------------------------------------------------------
// | parent_page_id (4) | page_id(4) |
// -----------------------------------
class BtreeBasePage
{
public:
    BtreeBasePage() = default;

    BtreeBasePage(BTreePageType type, uint32_t page_id, uint32_t parent_page_id, uint32_t max_size);

    ~BtreeBasePage() = default;

    bool is_leaf_page() const;

    bool is_root_page() const;

    int get_min_size() const; 

protected:    
    BTreePageType page_type_ = BTreePageType::INVALID_PAGE_TYPE;
    uint32_t log_seq_num_ = -1;
    uint32_t current_size_ = 0;
    uint32_t max_size_ = 0;
    uint32_t parent_page_id_ = -1;
    uint32_t page_id_ = -1;
};

// internal page dosen't contain data, it only store n key entries and n+1 child pointers (page_id)
// ----------------------------------------------------------------------------------
// | key(1) : ignore | page_id(1) | key(2) | page_id(2) | key(2) | page_id(3) | ... |
// ----------------------------------------------------------------------------------
// keys are stored in increasing order        
template <typename KeyType, typename ValueType, typename KeyComparator>
class BtreeInternalPage : public BtreeBasePage
{
public:
    BtreeInternalPage(uint32_t page_id, uint32_t parent_page_id, uint32_t max_size);

    ~BtreeInternalPage() = default;

    KeyType key(int index) const;

    void set_key(int index, const KeyType &key);

    void set_key(int index, KeyType &&key);

    int val_index(const ValueType &value) const;

    ValueType value(int index) const;    

    struct KV
    {
        KeyType key;
        ValueType value;
    };
private:
    std::vector<KV *> kv_vec_;
    std::mutex mutex_;
};


template <typename KeyType, typename ValueType, typename KeyComparator>
class BtreeLeafPage : public BtreeBasePage
{
public:
    struct KV
    {
        KeyType key;
        ValueType value;
    };

private:
    uint32_t next_page_id_;
    std::vector<KV *> kv_vec_;
    std::mutex mutex_;  
};

} // namespace burgerdb


#endif // BURGERDB_BTREE_H