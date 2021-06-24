#include "Interface.h"

void test01() {
    Interface iface;
    iface.printPrompt();
    iface.printInfo();
}

void test02() {
    Interface iface;
    iface.start();
}

int main() {
    test02();
}