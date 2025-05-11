//
// Created by o0kam1 on 25-4-13.
//

#include "Memory.h"

#include <cstdlib>
#include <efi.h>
#include <uefi.h>
#include <cstdint>
#include <cstdio>

Memory::Memory() : BaseModule() {
    uintn_t size = sizeof(EFI_MEMORY_DESCRIPTOR) * 31;
get_map:
    size += sizeof(EFI_MEMORY_DESCRIPTOR);
    const auto memMap = static_cast<EFI_MEMORY_DESCRIPTOR*>(malloc(size));
    uintn_t mapKey, descSize;
    uint32_t descVersion;
    const auto r = BS->GetMemoryMap(&size, memMap, &mapKey, &descSize, &descVersion);
    if (r == EFI_BUFFER_TOO_SMALL) {
        free(memMap);
        goto get_map;
    }

    auto desc = memMap;
    uintn_t totalPages = 0;
    uintn_t freePages = 0;
    while (reinterpret_cast<uintn_t>(desc) < reinterpret_cast<uintn_t>(memMap) + size) {
        switch (desc->Type) {
            case EfiConventionalMemory:
                freePages += desc->NumberOfPages;
            case EfiLoaderCode:
            case EfiLoaderData:
            case EfiBootServicesCode:
            case EfiBootServicesData:
            case EfiRuntimeServicesCode:
            case EfiRuntimeServicesData:
            case EfiPersistentMemory:
            case EfiACPIReclaimMemory:
            case EfiACPIMemoryNVS:
            case EfiPalCode:
            case EfiUnusableMemory:
                totalPages += desc->NumberOfPages;
                break;
            default:
                break;
        }
        desc = reinterpret_cast<EFI_MEMORY_DESCRIPTOR*>(reinterpret_cast<uintn_t>(desc) + descSize);
    }
    free(memMap);

    const size_t totalMiB = totalPages * EFI_PAGE_SIZE / 1024 / 1024;
    const size_t usedMiB = (totalPages - freePages) * EFI_PAGE_SIZE / 1024 / 1024;
    const size_t usedPercent = (usedMiB * 100) / totalMiB;
    sprintf(memory, "%zu MiB / %zu MiB (%zu%%)", usedMiB, totalMiB, usedPercent);
    itemCount = 1;
    const auto memoryItem = ModuleItem{"Memory", memory};
    items = new ModuleItem[itemCount];
    items[0] = memoryItem;
}

Memory::~Memory() {
    delete items;
}
