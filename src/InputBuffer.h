#ifndef BURGERDB_INPUTBUFFER_H
#define BURGERDB_INPUTBUFFER_H

#include <cstdlib>

namespace burgerdb {

struct InputBuffer {
    int read();

    char *buf = nullptr;
    size_t buf_len = 0;
    ssize_t input_len = 0;
};

} // namespace burgerdb

#endif // BURGERDB_INPUTBUFFER_H