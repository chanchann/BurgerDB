#ifndef METACMD_H
#define METACMD_H

#include <string>

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

class MetaCmd {
public:    
    static MetaCmdRes execute(std::string& cmd) {
        if(cmd == ".exit") {
            exit(EXIT_SUCCESS);
        } else {
            return MetaCmdRes::META_COMMAND_UNRECOGNIZED;
        }
    }
};


#endif // METACMD_H