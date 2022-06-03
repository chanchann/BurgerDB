#ifndef BURGERDB_ROW_H
#define BURGERDB_ROW_H

#include <stdint.h>
#include "Config.h"

namespace burgerdb {

struct Row {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
};
    
} // namespace burgerdb


#endif // BURGERDB_ROW_H