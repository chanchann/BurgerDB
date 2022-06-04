#include "MetaCmd.h"
#include "DB.h"
#include "InputBuffer.h"
#include <string.h>

namespace burgerdb {

MetaCmdRes MetaCmd::execute(const InputBuffer &input, DB *db){
    if(strcmp(input.buf, ".exit") == 0) {
        db->close();
    } else {
        return MetaCmdRes::UNRECOGNIZED;
    }
    return MetaCmdRes::SUCCESS;
}

} // namespace burgerdb
