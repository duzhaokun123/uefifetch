//
// Created by o0kam1 on 25-4-14.
//

#include <efi.h>
#include <uefi.h>
#include <libsmbios.h>
#include "SMBIOS.h"
#include "../utils.h"

size_t smbiosGetStructureSize(const SMBIOS_STRUCTURE_POINTER smbiosStructure) {
    size_t i;
    const char* stringTable = reinterpret_cast<char*>(reinterpret_cast<uint8_t*>(smbiosStructure.Hdr) + smbiosStructure.Hdr->Length);
    for (i = 1; stringTable[i - 1] != '\0' || stringTable[i] != '\0'; i++) {
    }
    return smbiosStructure.Hdr->Length + i + 1;
}

char* smbiosGetString(const SMBIOS_STRUCTURE_POINTER smbiosStructure, const uint8_t stringIndex) {
    const char* stringTable = reinterpret_cast<char*>(reinterpret_cast<uint8_t*>(smbiosStructure.Hdr) + smbiosStructure.Hdr->Length);
    for (uint8_t i = 1; i < stringIndex; i++) {
        while (stringTable[0] != '\0') {
            stringTable++;
        }
        stringTable++;
    }
    return const_cast<char*>(stringTable);
}

// TODO: split to multiple modules
SMBIOS::SMBIOS() : BaseModule() {
    constexpr efi_guid_t smbiosTableGuid = SMBIOS_TABLE_GUID;
    const auto smbiosTable = static_cast<SMBIOS_STRUCTURE_TABLE*>(getConfigurationTable(smbiosTableGuid));
    if (smbiosTable == nullptr) {
        return;
    }
    SMBIOS_STRUCTURE_POINTER smbiosStructure;
    smbiosStructure.Raw = reinterpret_cast<uint8_t*>(smbiosTable->TableAddress);
    items = new ModuleItem[smbiosTable->NumberOfSmbiosStructures];
    // items = new ModuleItem[smbiosTable->NumberOfSmbiosStructures + 1];
    // auto smbiosItemValue = new char[32];
    // sprintf(smbiosItemValue, "%d tables @0x%p", smbiosTable->NumberOfSmbiosStructures, smbiosTable->TableAddress);
    // items[itemCount] = ModuleItem{"SMBIOS", smbiosItemValue};
    // itemCount++;
    for (int i = 0; i < smbiosTable->NumberOfSmbiosStructures; i++) {
        switch (smbiosStructure.Hdr->Type) {
            case 0: {
                // BIOS
                const auto vendor = smbiosGetString(smbiosStructure, smbiosStructure.Type0->Vendor);
                const auto biosVersion = smbiosGetString(smbiosStructure, smbiosStructure.Type0->BiosVersion);
                const auto biosReleaseDate = smbiosGetString(smbiosStructure, smbiosStructure.Type0->BiosReleaseDate);
                const auto bios0ItemValue = new char[strlen(vendor) + strlen(biosVersion) + strlen(biosReleaseDate) + 6];
                sprintf(bios0ItemValue, "%s (%s, %s)", biosVersion, vendor, biosReleaseDate);
                items[itemCount] = ModuleItem{"BIOS", bios0ItemValue};
                itemCount++;
                break;
            }
            case 1: {
                // System
                const auto manufacturer = smbiosGetString(smbiosStructure, smbiosStructure.Type1->Manufacturer);
                const auto productName = smbiosGetString(smbiosStructure, smbiosStructure.Type1->ProductName);
                const auto version = smbiosGetString(smbiosStructure, smbiosStructure.Type1->Version);
                const auto bios1ItemValue = new char[strlen(manufacturer) + strlen(productName) + strlen(version) + 6];
                sprintf(bios1ItemValue, "%s (%s, %s)", productName, manufacturer, version);
                items[itemCount] = ModuleItem{"System", bios1ItemValue};
                itemCount++;
                break;
            }
            case 2: {
                // Baseboard
                const auto manufacturer = smbiosGetString(smbiosStructure, smbiosStructure.Type2->Manufacturer);
                const auto productName = smbiosGetString(smbiosStructure, smbiosStructure.Type2->ProductName);
                const auto version = smbiosGetString(smbiosStructure, smbiosStructure.Type2->Version);
                const auto bios2ItemValue = new char[strlen(manufacturer) + strlen(productName) + strlen(version) + 6];
                sprintf(bios2ItemValue, "%s (%s, %s)", productName, manufacturer, version);
                items[itemCount] = ModuleItem{"Baseboard", bios2ItemValue};
                itemCount++;
                break;
            }
            case 3: {
                // System Enclosure or Chassis
                break;
            }
            case 4: {
                // Processor
                const auto type = smbiosStructure.Type4->ProcessorType;
                const auto manufacturer = smbiosGetString(smbiosStructure, smbiosStructure.Type4->ProcessorManufacture);
                const auto version = smbiosGetString(smbiosStructure, smbiosStructure.Type4->ProcessorVersion);
                const auto maxSpeed = smbiosStructure.Type4->MaxSpeed[0] | (smbiosStructure.Type4->MaxSpeed[1] << 8);
                const auto bios4ItemValue = new char[strlen(manufacturer) + strlen(version) + 5 + 1 + 12];
                sprintf(bios4ItemValue, "%s (%s, %d MHz, %d)", version, manufacturer, maxSpeed, type);
                items[itemCount] = ModuleItem{"Processor", bios4ItemValue};
                itemCount++;
                break;
            }
            default:
                break;
        }
        smbiosStructure.Raw = reinterpret_cast<uint8_t*>(reinterpret_cast<size_t>(smbiosStructure.Raw) + smbiosGetStructureSize(smbiosStructure));
    }
}

SMBIOS::~SMBIOS() {
    for (int i = 0; i < itemCount; ++i) {
        delete items[i].value;
    }
    delete items;
}
