//
// Created by o0kam1 on 25-4-17.
//

#ifndef FOPEN_WRAP_H
#define FOPEN_WRAP_H

#include <uefi.h>

#ifndef _UEFI_H_
#error "fopen_wrap.h must be included after uefi.h"
#endif

inline FILE* fopen_wrap(const char_t *__filename, const char_t *__modes) {
    auto newModes = __modes;
    if (strcmp(__modes, CL("wb")) == 0) {
        newModes = CL("w");
    } else if (strcmp(__modes, CL("rb")) == 0) {
        newModes = CL("r");
    }
    return fopen(__filename, newModes);
}

#define fopen fopen_wrap

#endif //FOPEN_WRAP_H
