//
// Created by o0kam1 on 25-4-12.
//

#ifndef UTILS_H
#define UTILS_H

#include <efi.h>
#include <uefi.h>

void* getConfigurationTable(efi_guid_t targetGuid);

bool guidEqual(efi_guid_t a, efi_guid_t b);

void waitForKey();

void setCursorPosition(int x, int y);

void getCursorPosition(int* x, int* y);

void setTextColor(int attr);

int getTextColor();

bool haveShell();

int ip4MaskToCIDR(EFI_IPv4_ADDRESS* mask);

const char* pixelFormatToString(efi_gop_pixel_format_t format);

#endif //UTILS_H
