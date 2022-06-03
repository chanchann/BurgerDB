#ifndef BURGERDB_METACMD_H
#define BURGERDB_METACMD_H

#include <string>

namespace burgerdb {

enum class MetaCmdRes {
    COMMAND_SUCCESS,
    COMMAND_UNRECOGNIZED
};

std::string metaCmdResToStr(MetaCmdRes metaCmdRes) {
    switch(metaCmdRes) {
    case MetaCmdRes::COMMAND_SUCCESS:
        return "META_COMMAND_SUCCESS";
    case MetaCmdRes::COMMAND_UNRECOGNIZED:
        return "META_COMMAND_UNRECOGNIZED";
    default:
        return "META_UNKNOWN";
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