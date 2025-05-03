//
// Created by o0kam1 on 2025/04/29.
//

#include "GOP.h"
#include <efi.h>
#include <uefi.h>

#include "../utils.h"

GOP::GOP() {
    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_handle_t* handles = nullptr;
    uintn_t handleCount = 0;
    BS->LocateHandleBuffer(ByProtocol, &gopGuid, nullptr, &handleCount, &handles);
    items = new ModuleItem[handleCount];
    efi_gop_t* defaultGop;
    BS->HandleProtocol(&gopGuid, nullptr, reinterpret_cast<void**>(&defaultGop));
    for (uintn_t i = 0; i < handleCount; i++) {
        efi_gop_t* gop;
        BS->HandleProtocol(handles[i], &gopGuid, reinterpret_cast<void**>(&gop));
        const auto modeInfo = gop->Mode->Information;
        const auto itemName = new char[9];
        const auto itemValue = new char[32];
        sprintf(itemName, "GOP(%u)%s", static_cast<uint32_t>(i), gop == defaultGop ? "*" : "");
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
