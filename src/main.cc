#include "DB.h"
#include "InputBuffer.h"

using namespace burgerdb;

int main() {
    DB db;
    db.open("test.db");
    db.start_client();
    return 0;
}