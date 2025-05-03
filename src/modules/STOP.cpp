//
// Created by o0kam1 on 2025/04/29.
//

#include "STOP.h"
#include <efi.h>
#include <uefi.h>

STOP::STOP() {
    efi_guid_t stopGuid = EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID;
    efi_handle_t* handles = nullptr;
    uintn_t handleCount = 0;
    BS->LocateHandleBuffer(ByProtocol, &stopGuid, nullptr, &handleCount, &handles);
    items = new ModuleItem[handleCount];
    EFI_SIMPLE_TEXT_OUT_PROTOCOL* defaultStop;
    BS->LocateProtocol(&stopGuid, nullptr, reinterpret_cast<void**>(&defaultStop));
    for (uintn_t i = 0; i < handleCount; i++) {
        EFI_SIMPLE_TEXT_OUT_PROTOCOL* stop;
        BS->HandleProtocol(handles[i], &stopGuid, reinterpret_cast<void**>(&stop));
        const auto itemName = new char[11];
        const auto itemValue = new char[32];
        sprintf(itemName, "STOP (%u)%s", static_cast<uint32_t>(i), stop == defaultStop ? "*" : "");
        uintn_t width, height;
        stop->QueryMode(stop, stop->Mode->Mode, &width, &height);
        sprintf(itemValue, "%ux%u (text)", static_cast<uint32_t>(width), static_cast<uint32_t>(height));
        items[itemCount] = ModuleItem{itemName, itemValue};
        itemCount++;
    }
}

STOP::~STOP() {
    for (int i = 0; i < itemCount; i++) {
        delete items[i].name;
        delete items[i].value;
    }
    delete items;
}
