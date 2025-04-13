//
// Created by o0kam1 on 25-4-12.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include "BaseModule.h"

class Display : public BaseModule {
public:
    Display();
    ~Display();

private:
    char textMode[32] = {};
    char graphicsMode[32] = {};
};

#endif //DISPLAY_H
