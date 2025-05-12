//
// Created by o0kam1 on 25-4-12.
//

#include <uefienv.h>
#include "utils.h"
#include <cstdio>
#include <cstring>

void* getConfigurationTable(EFI_GUID targetGuid) {
    for (uintn_t i = 0; i < ST->NumberOfTableEntries; i++) {
        const auto guid = ST->ConfigurationTable[i].VendorGuid;
        if (guidEqual(targetGuid, guid)) {
            return ST->ConfigurationTable[i].VendorTable;
        }
    }
    return nullptr;
}

bool guidEqual(const EFI_GUID a, const EFI_GUID b) {
    return a.Data1 == b.Data1 && a.Data2 == b.Data2 && a.Data3 == b.Data3 && memcmp(a.Data4, b.Data4, sizeof(a.Data4)) == 0;
}

void waitForKey() {
    getchar();
}

void setCursorPosition(const int x, const int y) {
    ST->ConOut->SetCursorPosition(ST->ConOut, x, y);
}

void getCursorPosition(int* x, int* y) {
    *x = ST->ConOut->Mode->CursorColumn;
    *y = ST->ConOut->Mode->CursorRow;
}

void setTextColor(const int attr) {
    ST->ConOut->SetAttribute(ST->ConOut, attr);
}

int getTextColor() {
    return ST->ConOut->Mode->Attribute;
}

bool haveShell() {
    EFI_SHELL_PROTOCOL* efiShellProtocol;
    EFI_GUID efiShellProtocolGuid = EFI_SHELL_PROTOCOL_GUID;
    return BS->LocateProtocol(&efiShellProtocolGuid, nullptr, reinterpret_cast<void**>(&efiShellProtocol)) == EFI_SUCCESS;
}

int ip4MaskToCIDR(EFI_IPv4_ADDRESS* mask) {
    auto cidr = 0;
    for (const auto i: mask->Addr) {
        for (int j = 0; j < 8; j++) {
            if ((i << j & 0b10000000) != 0) {
                cidr++;
            } else {
                return cidr;
            }
        }
    }
    return cidr;
}

const char* pixelFormatToString(EFI_GRAPHICS_PIXEL_FORMAT format) {
    switch (format) {
        case PixelBlueGreenRedReserved8BitPerColor:
            return "BGRX8888";
        case PixelRedGreenBlueReserved8BitPerColor:
            return "RGBX8888";
        case PixelBitMask:
            return "BitMask";
        case PixelBltOnly:
            return "BltOnly";
        default:
            return "unknown";
    }
}
