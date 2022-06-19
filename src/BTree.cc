#include "BTree.h"
#include "Row.h"
#include "Config.h"

namespace burgerdb {

BtreeBasePage::BtreeBasePage(BTreePageType type, uint32_t page_id, uint32_t parent_page_id, uint32_t max_size)
    : page_type_(type),
    max_size_(max_size),
    page_id_(page_id),
    parent_page_id_(parent_page_id) 
{
}

bool BtreeBasePage::is_leaf_page() const
{
    return page_type_ == BTreePageType::LEAF_PAGE;
}

bool BtreeBasePage::is_root_page() const 
{
    return parent_page_id_ == INVALID_PAGE_ID;
}

// Generally, min page size == max page size / 2
int BtreeBasePage::get_min_size() const
{
    return max_size_ / 2;
}

template<typename KeyType, typename ValueType, typename KeyComparator>
BtreeInternalPage<KeyType, ValueType, KeyComparator>::BtreeInternalPage(uint32_t page_id, uint32_t parent_page_id, uint32_t max_size)
    : BtreeBasePage(BTreePageType::INTERNAL_PAGE, page_id, parent_page_id, max_size)
{
}

template<typename KeyType, typename ValueType, typename KeyComparator>
KeyType BtreeInternalPage<KeyType, ValueType, KeyComparator>::key(int index) const
{
    assert(index < kv_vec_.size());
    return kv_vec_[index].key;
}

template<typename KeyType, typename ValueType, typename KeyComparator>
void BtreeInternalPage<KeyType, ValueType, KeyComparator>::set_key(int index, const KeyType &key)
{
    assert(index < kv_vec_.size());
    kv_vec_[index].key = key;
}

template<typename KeyType, typename ValueType, typename KeyComparator>
void BtreeInternalPage<KeyType, ValueType, KeyComparator>::set_key(int index, KeyType &&key)
{
    assert(index < kv_vec_.size());
    kv_vec_[index].key = std::move(key);
}

template<typename KeyType, typename ValueType, typename KeyComparator>
int BtreeInternalPage<KeyType, ValueType, KeyComparator>::val_index(const ValueType &value) const
{
    // key has order but value dosen't, so we scan to search
    for(uint32_t i = 0; i < current_size_; i++) 
    {
        if(kv_vec_[i].value == value) 
        {
            return i;
        }
    }
    return -1;
}

template<typename KeyType, typename ValueType, typename KeyComparator>
ValueType BtreeInternalPage<KeyType, ValueType, KeyComparator>::value(int index) const
{
    assert(index < kv_vec_.size());
    return kv_vec_[index].value;
}

} // namespace burgerdb
