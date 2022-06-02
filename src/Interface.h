#ifndef BURGERDB_INTERFACE_H
#define BURGERDB_INTERFACE_H

namespace burgerdb
{

class Interface {
public:
    Interface() = default;

    void printPrompt();
    
    void printInfo();
    
    void start();

};
    
} // namespace burgerdb

#endif // BURGERDB_INTERFACE_H