//
// Created by o0kam1 on 25-4-12.
//

#include <efi.h>
#include <uefi.h>
#include "Shell.h"

#include <cstdio>

Shell::Shell() : BaseModule() {
    EFI_SHELL_PROTOCOL* efiShellProtocol;
    EFI_GUID efiShellProtocolGuid = EFI_SHELL_PROTOCOL_GUID;
    if (BS->LocateProtocol(&efiShellProtocolGuid, nullptr, reinterpret_cast<void**>(&efiShellProtocol)) != EFI_SUCCESS) {
        sprintf(shellName, "none");
    } else {
        sprintf(shellName, "(U)EFI Shell %d.%d", efiShellProtocol->MajorVersion, efiShellProtocol->MinorVersion);
    }

    const auto shellNameItem = ModuleItem{"Shell", shellName};
    itemCount = 1;
    items = new ModuleItem[itemCount];
    items[0] = shellNameItem;
}

Shell::~Shell() {
    delete items;
}
