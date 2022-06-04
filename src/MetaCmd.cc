#include "MetaCmd.h"
#include "DB.h"
#include "InputBuffer.h"
#include <string.h>

namespace burgerdb {

MetaCmdRes MetaCmd::execute(const InputBuffer &input, DB *db){
    if(strcmp(input.buf, ".exit") == 0) {
        db->close();
        exit(EXIT_SUCCESS);  // todo : more elegant
    } else {
        return MetaCmdRes::COMMAND_UNRECOGNIZED;
    }
}

} // namespace burgerdb
