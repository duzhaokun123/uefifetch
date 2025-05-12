//
// Created by o0kam1 on 25-4-12.
//

#include "UEFI.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <uefienv.h>

UEFI::UEFI() : BaseModule() {
    const auto vendor = static_cast<char*>(malloc(BUFSIZ));
    wcstombs(vendor, reinterpret_cast<wchar_t*>(ST->FirmwareVendor), BUFSIZ);
    sprintf(uefiVersion, "%d.%d (%s, 0x%08X)", ST->Hdr.Revision >> 16, ST->Hdr.Revision & 0xFFFF, vendor, ST->FirmwareRevision);
    const auto uefiVersionItem = ModuleItem{"UEFI", uefiVersion};
    free(vendor);

    itemCount = 1;
    items = new ModuleItem[itemCount];
    items[0] = uefiVersionItem;
}

UEFI::~UEFI() {
    delete items;
}

