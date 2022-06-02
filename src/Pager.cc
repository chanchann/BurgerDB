#include "Pager.h"
#include <fcntl.h>
#include <unistd.h>

namespace burgerdb {

int Pager::open(const std::string &filename) {
    int fd = open(filename.c_str(),
                    O_RDWR |      // Read/Write mode
                        O_CREAT,  // Create file if it does not exist
                    S_IWUSR |     // User write permission
                        S_IRUSR   // User read permission
                    );

    if (fd == -1) {
        fprintf(stderr, "Unable to open file\n");
        exit(EXIT_FAILURE);
    }
    off_t file_length = lseek(fd, 0, SEEK_END);

    fd_ = fd;
    file_len_ = file_length;

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pages_[i] = nullptr;
    }
}

} // namespace burgerdb
