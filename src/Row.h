#ifndef BURGERDB_ROW_H
#define BURGERDB_ROW_H

#include <stdint.h>

namespace burgerdb {

struct Row {
    void serialize(uint8_t* dest);

    void deserialize(uint8_t* src);

    void print();

    static const uint32_t COLUMN_USERNAME_SIZE = 32;
    static const uint32_t COLUMN_EMAIL_SIZE = 255;

    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
};
    
} // namespace burgerdb


#endif // BURGERDB_ROW_H