#ifndef BURGERDB_METACMD_H
#define BURGERDB_METACMD_H

#include <string>

namespace burgerdb {

enum class MetaCmdRes {
    SUCCESS,
    UNRECOGNIZED
};

class DB;
class InputBuffer;

class MetaCmd {
public:    
    static MetaCmdRes execute(const InputBuffer &buf, DB *db);
};

} // namespace burgerdb

#endif // BURGERDB_METACMD_H