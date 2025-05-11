//
// Created by o0kam1 on 25-4-14.
//

#include "FS2.h"
#include <efi.h>
#include <uefi.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

FS2::FS2() : BaseModule() {
    EFI_HANDLE* handles = nullptr;
    EFI_GUID simpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_GUID fileSystemInfoId = EFI_FILE_SYSTEM_INFO_ID;
    uintn_t handleCount = 0;
    BS->LocateHandleBuffer(ByProtocol, &simpleFileSystemProtocolGuid, nullptr, &handleCount, &handles);
    items = new ModuleItem[handleCount];
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* defaultSFSP;
    BS->HandleProtocol(LIP->DeviceHandle, &simpleFileSystemProtocolGuid, reinterpret_cast<void**>(&defaultSFSP));
    for (uintn_t i = 0; i < handleCount; i++) {
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* simpleFileSystemProtocol;
        BS->HandleProtocol(handles[i], &simpleFileSystemProtocolGuid, reinterpret_cast<void**>(&simpleFileSystemProtocol));
        EFI_FILE_PROTOCOL* root;
        simpleFileSystemProtocol->OpenVolume(simpleFileSystemProtocol, &root);
        uintn_t bufferSize = 0;
        root->GetInfo(root, &fileSystemInfoId, &bufferSize, nullptr);
        const auto fileSystemInfo = static_cast<EFI_FILE_SYSTEM_INFO*>(malloc(bufferSize));
        root->GetInfo(root, &fileSystemInfoId, &bufferSize, fileSystemInfo);
        const auto label = new char[32];
        wcstombs(label, reinterpret_cast<wchar_t*>(fileSystemInfo->VolumeLabel), fileSystemInfo->Size - SIZE_OF_EFI_FILE_SYSTEM_INFO);
        const size_t totalMiB = fileSystemInfo->VolumeSize / 1024 / 1024;
        const size_t usedMiB = (fileSystemInfo->VolumeSize - fileSystemInfo->FreeSpace) / 1024 / 1024;
        const size_t usedPercent = usedMiB * 100 / totalMiB;
        const auto itemName = new char[strlen(label) + 8];
        const auto itemValue = new char[40];
        sprintf(itemName, "FS (%s)%s", label, simpleFileSystemProtocol == defaultSFSP ? "*" : "");
        sprintf(itemValue, "%zu MiB / %zu MiB (%zu%%)", usedMiB, totalMiB, usedPercent);
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
