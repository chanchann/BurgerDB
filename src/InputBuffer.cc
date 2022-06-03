#include "InputBuffer.h"
#include "Status.h"
#include <string>

namespace burgerdb {

int InputBuffer::read() {
    ssize_t bytes_read = getline(&buf, &buf_len, stdin);
    if(bytes_read <= 0) {
        return READ_STDIN_ERROR;
    }
    // Ignore trailing newline
    input_len = bytes_read - 1;
    buf[bytes_read - 1] = 0;
    return SUCCESS;
}


} // namespace burgerdb
