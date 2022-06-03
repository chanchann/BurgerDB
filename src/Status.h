#ifndef BURGERDB_STATUS_H
#define BURGERDB_STATUS_H

namespace burgerdb {

enum Status {
    SUCCESS, 
    OPEN_FILE_ERROR,
    READ_FILE_ERROR,
    READ_STDIN_ERROR,
    PAGE_OUT_OF_BOUND,
};

} // namespace burgerdb


#endif // BURGERDB_STATUS_H