//
// Created by o0kam1 on 25-4-13.
//

#ifndef MEMORY_H
#define MEMORY_H
#include "BaseModule.h"

class Memory : public BaseModule {
public:
    Memory();
    ~Memory();
private:
    char memory[30] = {};
};

#endif //MEMORY_H
