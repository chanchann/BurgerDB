#include "Row.h"
#include "Config.h"
#include <string.h>
#include <stdio.h>

namespace burgerdb {

void Row::serialize(uint8_t* dest) {
    memcpy(dest + ID_OFFSET, &id, ID_SIZE);
    memcpy(dest + USERNAME_OFFSET, &username, USERNAME_SIZE);
    memcpy(dest + EMAIL_OFFSET, &email, EMAIL_SIZE);
}

void Row::deserialize(uint8_t* src) {
    memcpy(&id, src + ID_OFFSET, ID_SIZE);
    memcpy(&username, src + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&email, src + EMAIL_OFFSET, EMAIL_SIZE);
}

void Row::print() {
    fprintf(stderr, "(%d, %s, %s)\n", id, username, email);
}

} // namespace burgerdb
