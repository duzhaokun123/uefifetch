//
// Created by o0kam1 on 25-4-12.
//

#ifndef module_UEFI_H
#define module_UEFI_H
#include "BaseModule.h"

class UEFI : public BaseModule {
public:
    UEFI();
    ~UEFI();
private:
    char uefiVersion[50] = {};
};

#endif
