//
// Created by o0kam1 on 2025/04/29.
//

#include "GOP.h"
#include <efi.h>
#include <uefi.h>
#include <cstdint>
#include <cstdio>

#include "../utils.h"

GOP::GOP() {
    EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_HANDLE* handles = nullptr;
    uintn_t handleCount = 0;
    BS->LocateHandleBuffer(ByProtocol, &gopGuid, nullptr, &handleCount, &handles);
    items = new ModuleItem[handleCount];
    EFI_GRAPHICS_OUTPUT_PROTOCOL* defaultGop;
    BS->LocateProtocol(&gopGuid, nullptr, reinterpret_cast<void**>(&defaultGop));
    for (uintn_t i = 0; i < handleCount; i++) {
        EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
        BS->HandleProtocol(handles[i], &gopGuid, reinterpret_cast<void**>(&gop));
        const auto modeInfo = gop->Mode->Info;
        const auto itemName = new char[10];
        const auto itemValue = new char[32];
        sprintf(itemName, "GOP (%u)%s", static_cast<uint32_t>(i), gop == defaultGop ? "*" : "");
        sprintf(itemValue, "%dx%d (%s)", modeInfo->HorizontalResolution, modeInfo->VerticalResolution, pixelFormatToString(modeInfo->PixelFormat));
        items[itemCount] = ModuleItem{itemName, itemValue};
        itemCount++;
    }
}

GOP::~GOP() {
    for (int i = 0; i < itemCount; i++) {
        delete items[i].name;
        delete items[i].value;
    }
    delete items;
}
