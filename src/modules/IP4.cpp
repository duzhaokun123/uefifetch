//
// Created by o0kam1 on 25-4-14.
//

#include <efi.h>
#include <uefi.h>
#include "IP4.h"
#include "../protocols/EFI_IP4_CONFIG2_PROTOCOL.h"
#include "../utils.h"

IP4::IP4() : BaseModule() {
    efi_handle_t* handles = nullptr;
    efi_guid_t ip4ServiceBindingProtocolGuid = EFI_IP4_SERVICE_BINDING_PROTOCOL;
    efi_guid_t ip4Config2ProtocolGuid = EFI_IP4_CONFIG2_PROTOCOL_GUID;
    uintn_t handleCount = 0;
    auto r = BS->LocateHandleBuffer(ByProtocol, &ip4ServiceBindingProtocolGuid, nullptr, &handleCount, &handles);
    if (r != EFI_SUCCESS) {
        return;
    }
    items = new ModuleItem[handleCount];
    for (uintn_t i = 0; i < handleCount; i++) {
        EFI_IP4_CONFIG2_PROTOCOL* ip4Config2Protocol;
        r = BS->HandleProtocol(handles[i], &ip4Config2ProtocolGuid, reinterpret_cast<void**>(&ip4Config2Protocol));
        if (r != EFI_SUCCESS) {
            continue;
        }
        uintn_t dataSize = 0;
        ip4Config2Protocol->GetData(ip4Config2Protocol, Ip4Config2DataTypeInterfaceInfo, &dataSize, nullptr);
        const auto ifInfo = static_cast<EFI_IP4_CONFIG2_INTERFACE_INFO*>(malloc(dataSize));
        ip4Config2Protocol->GetData(ip4Config2Protocol, Ip4Config2DataTypeInterfaceInfo, &dataSize, ifInfo);
        const auto ifName = static_cast<char*>(malloc(EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE));
        wcstombs(ifName, reinterpret_cast<wchar_t*>(ifInfo->Name), EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE);
        const auto cidrMask = ip4MaskToCIDR(&ifInfo->SubnetMask);
        const auto itemName = static_cast<char*>(malloc(sizeof(char) * (strlen(ifName) + 7)));
        const auto itemValue = static_cast<char*>(malloc(sizeof(char) * 19));
        sprintf(itemName, "IP4 (%s)", ifName);
        sprintf(itemValue, "%d.%d.%d.%d/%d", ifInfo->StationAddress.Addr[0], ifInfo->StationAddress.Addr[1], ifInfo->StationAddress.Addr[2], ifInfo->StationAddress.Addr[3], cidrMask);
        items[itemCount] = ModuleItem{itemName, itemValue};
        itemCount++;
        free(ifName);
        free(ifInfo);
    }
}

IP4::~IP4() {
    for (int i = 0; i < itemCount; i++) {
        free((void*) items[i].name);
        free((void*) items[i].value);
    }
    delete items;
}
