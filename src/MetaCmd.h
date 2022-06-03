#ifndef BURGERDB_METACMD_H
#define BURGERDB_METACMD_H

#include <string>

namespace burgerdb {

enum class MetaCmdRes {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED
};

std::string metaCmdResToStr(MetaCmdRes metaCmdRes) {
    switch(metaCmdRes) {
    case MetaCmdRes::META_COMMAND_SUCCESS:
        return "META_COMMAND_SUCCESS";
    case MetaCmdRes::META_COMMAND_UNRECOGNIZED:
        return "META_COMMAND_UNRECOGNIZED";
    default:
        return "UNKNOWN";
    }
}

class DB;
class InputBuffer;

class MetaCmd {
public:    
    static MetaCmdRes execute(const InputBuffer &buf, DB *db);
};

} // namespace burgerdb

#endif // BURGERDB_METACMD_H