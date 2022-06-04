#include "Pager.h"
#include "Status.h"

#include <fcntl.h>
#include <unistd.h>

namespace burgerdb {

int Pager::init(const std::string &filename) {
    int fd = open(filename.c_str(),
                    O_RDWR |      // Read/Write mode
                        O_CREAT,  // Create file if it does not exist
                    S_IWUSR |     // User write permission
                        S_IRUSR   // User read permission
                    );
    // todo : call it once?
    if (fd == -1) {
        fprintf(stderr, "Unable to open file\n");
        return OPEN_FILE_ERROR;
    }
    // SEEK_END : The file offset is set to the size of the file plus offset bytes.
    off_t file_len = lseek(fd_, 0, SEEK_END);

    fd_ = fd;
    file_len_ = static_cast<uint32_t>(file_len);

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pages_[i] = nullptr;
    }
    return SUCCESS;
}

int Pager::get(uint32_t page_num, uint8_t **page) {
    if (page_num > TABLE_MAX_PAGES) {
        fprintf(stderr, "Tried to fetch page number out of bounds. %d > %d\n", page_num,
            TABLE_MAX_PAGES);
        *page = nullptr;
        return PAGE_OUT_OF_BOUND;
    }
    if(pages_[page_num] == nullptr) {
        // Cache miss. Allocate memory and load from file.
        uint8_t *new_page = new uint8_t[PAGE_SIZE];
        uint32_t num_pages = file_len_ / PAGE_SIZE;
        // We might save a partial page at the end of the file
        if(file_len_ % PAGE_SIZE) {
            num_pages += 1;
        }
        if(page_num < num_pages) {
            // SEEK_SET : The file offset is set to offset bytes.
            lseek(fd_, page_num * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(fd_, new_page, PAGE_SIZE);
            if(bytes_read == -1) {
                fprintf(stderr, "Error reading file: %d\n", errno);
                delete[] new_page;
                new_page = nullptr;
                // TODO : should I just exit?
                return READ_FILE_ERROR;
            }
        }
        pages_[page_num] = new_page;
    }

    page = &pages_[page_num];
    return SUCCESS;
}

int Pager::flush(uint32_t page_num, uint32_t size) {
    if(pages_[page_num] == nullptr) {
        return FLUSH_NULL_PAGE;
    }
    off_t offset = lseek(fd_, page_num * PAGE_SIZE, SEEK_SET);
    if(offset == -1) {
        return SEEK_ERROR;
    }
    ssize_t bytes_written = write(fd_, pages_[page_num], size);

    if(bytes_written == -1) {
        return WRITE_FILE_ERROR;
    }
    return SUCCESS;
}

int Pager::free(uint32_t index) {
    delete[] pages_[index];
    pages_[index] = nullptr;
    return SUCCESS;
}

int Pager::close() {
    int result = ::close(fd_);
    if(result == -1) {
        return CLOSE_FILE_ERROR;
    }
    // todo : why loop to free again ?
    for(uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        if(pages_[i]) {
            free(i);
        }
    }
    return SUCCESS;
}

} // namespace burgerdb
