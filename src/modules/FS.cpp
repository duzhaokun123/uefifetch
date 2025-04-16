//
// Created by o0kam1 on 25-4-14.
//

#include <efi.h>
#include <uefi.h>
#include "FS.h"

FS::FS() : BaseModule() {
    efi_guid_t simpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    efi_simple_file_system_protocol_t* simpleFileSystemProtocol;
    auto r = BS->HandleProtocol(LIP->DeviceHandle, &simpleFileSystemProtocolGuid, reinterpret_cast<void**>(&simpleFileSystemProtocol));
    if (r != EFI_SUCCESS) {
        return;
    }
    efi_file_handle_t* root;
    simpleFileSystemProtocol->OpenVolume(simpleFileSystemProtocol, &root);
    efi_guid_t fileSystemInfoId = EFI_FILE_SYSTEM_INFO_ID;
    uintn_t bufferSize = 0;
    root->GetInfo(root, &fileSystemInfoId, &bufferSize, nullptr);
    const auto fileSystemInfo = static_cast<EFI_FILE_SYSTEM_INFO*>(malloc(bufferSize));
    root->GetInfo(root, &fileSystemInfoId, &bufferSize, fileSystemInfo);
    const auto totalMiB = fileSystemInfo->VolumeSize / 1024 / 1024;
    const auto usedMiB = (fileSystemInfo->VolumeSize - fileSystemInfo->FreeSpace) / 1024 / 1024;
    auto usedPercent = 0;
    if (totalMiB != 0) {
        usedPercent = (usedMiB * 100) / totalMiB;
    }
    sprintf(value, "%d MiB / %d MiB (%d%%)", usedMiB, totalMiB, usedPercent);
    itemCount = 1;
    const auto fsItem = ModuleItem{"FS (.)", value};
    items = new ModuleItem[itemCount];
    items[0] = fsItem;
    free(fileSystemInfo);
}

FS::~FS() {
    delete items;
}
