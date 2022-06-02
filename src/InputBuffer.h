#ifndef BURGERDB_INPUTBUFFER_H
#define BURGERDB_INPUTBUFFER_H

#include <cstdlib>

namespace burgerdb {

struct InputBuffer {
    char *buf;
    size_t buf_len;
    ssize_t input_len;
};

} // namespace burgerdb

#endif // BURGERDB_INPUTBUFFER_H