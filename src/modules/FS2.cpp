//
// Created by o0kam1 on 25-4-14.
//

#include "FS2.h"
#include <efi.h>
#include <uefi.h>

FS2::FS2() : BaseModule() {
    efi_handle_t* handles = nullptr;
    efi_guid_t simpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    efi_guid_t fileSystemInfoId = EFI_FILE_SYSTEM_INFO_ID;
    uintn_t handleCount = 0;
    BS->LocateHandleBuffer(ByProtocol, &simpleFileSystemProtocolGuid, nullptr, &handleCount, &handles);
    items = new ModuleItem[handleCount];
    for (uintn_t i = 0; i < handleCount; i++) {
        efi_simple_file_system_protocol_t* simpleFileSystemProtocol;
        BS->HandleProtocol(handles[i], &simpleFileSystemProtocolGuid, reinterpret_cast<void**>(&simpleFileSystemProtocol));
        efi_file_handle_t* root;
        simpleFileSystemProtocol->OpenVolume(simpleFileSystemProtocol, &root);
        uintn_t bufferSize = 0;
        root->GetInfo(root, &fileSystemInfoId, &bufferSize, nullptr);
        const auto fileSystemInfo = static_cast<EFI_FILE_SYSTEM_INFO*>(malloc(bufferSize));
        root->GetInfo(root, &fileSystemInfoId, &bufferSize, fileSystemInfo);
        const auto label = new char[32];
        wcstombs(label, reinterpret_cast<wchar_t*>(fileSystemInfo->VolumeLabel), fileSystemInfo->Size - SIZE_OF_EFI_FILE_SYSTEM_INFO);
        const auto totalMiB = fileSystemInfo->VolumeSize / 1024 / 1024;
        const auto usedMiB = (fileSystemInfo->VolumeSize - fileSystemInfo->FreeSpace) / 1024 / 1024;
        const auto usedPercent = usedMiB * 100 / totalMiB;
        const auto itemName = new char[strlen(label) + 7];
        const auto itemValue = new char[40];
        sprintf(itemName, "FS (%s)", label);
        sprintf(itemValue, "%d MiB / %d MiB (%d%%)", usedMiB, totalMiB, usedPercent);
        items[i] = ModuleItem{itemName, itemValue};
        itemCount++;
        free(label);
        free(fileSystemInfo);
    }
}

FS2::~FS2() {
    for (int i = 0; i < itemCount; i++) {
        delete items[i].name;
        delete items[i].value;
    }
    delete items;
}
