#ifndef BURGERDB_STATUS_H
#define BURGERDB_STATUS_H

namespace burgerdb {

enum Status {
    SUCCESS, 
    OPEN_FILE_ERROR,
    READ_FILE_ERROR,
    READ_STDIN_ERROR,
    PAGE_OUT_OF_BOUND,
    FLUSH_NULL_PAGE,
    SEEK_ERROR,
    WRITE_FILE_ERROR,
    CLOSE_FILE_ERROR,
    SEEK_FILE_ERROR,
    CORRUPTED_FILE,     // file is not a whole number of pages
};

} // namespace burgerdb


#endif // BURGERDB_STATUS_H