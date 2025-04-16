//
// Created by o0kam1 on 25-4-12.
//

#include "display.h"
#include <uefi.h>

Display::Display() : BaseModule() {
    const auto mode = ST->ConOut->Mode->Mode;
    uintn_t col, row;
    ST->ConOut->QueryMode(ST->ConOut, mode, &col, &row);
    sprintf(textMode, "%dx%d (text)", col, row);
    const auto textModeItem = ModuleItem{"Display", textMode};

    auto gopGuid = efi_guid_t EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t* gop = nullptr;
    BS->LocateProtocol(&gopGuid, nullptr, reinterpret_cast<void**>(&gop));
    sprintf(graphicsMode, "%dx%d (graphics)", gop->Mode->Information->HorizontalResolution, gop->Mode->Information->VerticalResolution);
    const auto graphicsModeItem = ModuleItem{"Display", graphicsMode};

    itemCount = 2;
    items = new ModuleItem[itemCount];
    items[0] = textModeItem;
    items[1] = graphicsModeItem;
}

Display::~Display() {
    delete[] items;
}
