//
// Created by o0kam1 on 25-4-12.
//

#ifndef UTILS_H
#define UTILS_H

#include <efi.h>

void* getConfigurationTable(EFI_GUID targetGuid);

bool guidEqual(EFI_GUID a, EFI_GUID b);

void waitForKey();

void setCursorPosition(int x, int y);

void getCursorPosition(int* x, int* y);

void setTextColor(int attr);

int getTextColor();

bool haveShell();

int ip4MaskToCIDR(EFI_IPv4_ADDRESS* mask);

const char* pixelFormatToString(EFI_GRAPHICS_PIXEL_FORMAT format);

#endif //UTILS_H
