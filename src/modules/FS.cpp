//
// Created by o0kam1 on 25-4-14.
//

#include <efi.h>
#include <uefi.h>
#include "FS.h"

FS::FS() : BaseModule() {
    efi_guid_t simpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    efi_simple_file_system_protocol_t* simpleFileSystemProtocol;
    BS->HandleProtocol(LIP->DeviceHandle, &simpleFileSystemProtocolGuid, reinterpret_cast<void**>(&simpleFileSystemProtocol));
    efi_file_handle_t* root;
    simpleFileSystemProtocol->OpenVolume(simpleFileSystemProtocol, &root);
    efi_guid_t fileSystemInfoId = EFI_FILE_SYSTEM_INFO_ID;
    uintn_t bufferSize = 0;
    EFI_FILE_SYSTEM_INFO* fileSystemInfo;
    root->GetInfo(root, &fileSystemInfoId, &bufferSize, nullptr);
    root->GetInfo(root, &fileSystemInfoId, &bufferSize, &fileSystemInfo);
    const auto label = new char[32];
    wcstombs(label, reinterpret_cast<wchar_t*>(fileSystemInfo->VolumeLabel), fileSystemInfo->Size - SIZE_OF_EFI_FILE_SYSTEM_INFO);
    const auto totalMiB = fileSystemInfo->VolumeSize / 1024 / 1024;
    const auto usedMiB = (fileSystemInfo->VolumeSize - fileSystemInfo->FreeSpace) / 1024 / 1024;
    auto usedPercent = 0;
    if (totalMiB != 0) {
        usedPercent = (usedMiB * 100) / totalMiB;
    }
    sprintf(name, "FS (%s)", label);
    sprintf(value, "%d/%d (%d%%)", usedMiB, totalMiB, usedPercent);
    itemCount = 1;
    const auto fsItem = ModuleItem{name, value};
    items = new ModuleItem[itemCount];
    items[0] = fsItem;
    delete label;
}

FS::~FS() {
    delete items;
}
