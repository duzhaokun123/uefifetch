//
// Created by o0kam1 on 25-4-14.
//

#ifndef DISK_H
#define DISK_H
#include "BaseModule.h"


class FS : public BaseModule {
public:
    FS();
    ~FS();

private:
    char value[64] = {};
};


#endif //DISK_H
