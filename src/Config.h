#ifndef BURGERDB_CONFIG_H
#define BURGERDB_CONFIG_H

#include "Row.h"

namespace burgerdb {

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

static constexpr uint32_t PAGE_SIZE = 4096;
static constexpr uint32_t TABLE_MAX_PAGES = 100;

static constexpr uint32_t INVALID_PAGE_ID = -1;  


} // namespace burgerdb


#endif // BURGERDB_CONFIG_H