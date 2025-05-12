//
// Created by o0kam1 on 2025/05/13.
//

#ifndef UEFIENV_H
#define UEFIENV_H

#include <efi.h>

#ifdef __cplusplus
extern "C" {
#endif

extern EFI_SYSTEM_TABLE* ST;
extern EFI_RUNTIME_SERVICES* RT;
extern EFI_BOOT_SERVICES* BS;
extern EFI_LOADED_IMAGE_PROTOCOL* LIP;

typedef INTN intn_t;
typedef UINTN uintn_t;

#ifdef __cplusplus
}
#endif

#endif //UEFIENV_H
