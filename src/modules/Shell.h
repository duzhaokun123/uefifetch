//
// Created by o0kam1 on 25-4-12.
//

#ifndef SHELL_H
#define SHELL_H

#include "BaseModule.h"

class Shell : public BaseModule {
public:
    Shell();
    ~Shell();
private:
    char shellName[20] = {};
};

#endif //SHELL_H
