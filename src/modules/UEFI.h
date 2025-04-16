//
// Created by o0kam1 on 25-4-12.
//

#ifndef UEFI_H
#define UEFI_H
#include "BaseModule.h"

class UEFI : public BaseModule {
public:
    UEFI();
    ~UEFI();
private:
    char uefiVersion[50] = {};
};

#endif //UEFI_H
