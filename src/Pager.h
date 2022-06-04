#ifndef BURGERDB_PAGER_H
#define BURGERDB_PAGER_H

#include <cstdlib>
#include <cstdint>
#include <string>
#include "Config.h"

namespace burgerdb {

// We ask the pager for page number x, and the pager gives us back a block of memory. 
// It first looks in its cache. 
// On a cache miss, it copies data from disk into memory (by reading the database file)
// The Pager accesses the page cache and the file. 
// The Table object makes requests for pages through the pager:
class Pager {
public:
    // opens the database file and keeps track of its size.
    int init(const std::string &filename);

    int get(uint32_t page_num, uint8_t **page);

    int flush(uint32_t page_num, uint32_t size);

    int free(uint32_t index);

    int close();

    uint32_t file_len() { return file_len_; }

    uint8_t **pages() { return pages_; }

    uint8_t *pages(uint32_t index) { return pages_[index]; }

private:
    int fd_;
    uint32_t file_len_;
    uint8_t *pages_[TABLE_MAX_PAGES];
};
    

    
} // namespace burgerdb


#endif // BURGERDB_PAGER_H