#include "DbClient.h"

void test01() {
    DbClient iface;
    iface.printPrompt();
    iface.printInfo();
}

void test02() {
    DbClient iface;
    iface.start();
}

int main() {
    test02();
}