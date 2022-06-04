#include "DB.h"
#include "InputBuffer.h"

using namespace burgerdb;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Must supply a database filename.\n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];
    DB db;
    db.open(filename);
    db.start_client();
    return 0;
}