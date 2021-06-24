#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>

class Interface {
public:
    Interface();
    void printPrompt();
    void printInfo();
    
    void start();
private:
    bool quit_;
};


#endif // INTERFACE_H