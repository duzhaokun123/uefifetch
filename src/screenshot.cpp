//
// Created by o0kam1 on 25-4-17.
//

#include <efi.h>
#include <uefi.h>
#include "screenshot.h"
#include <lodepng.h>

uint8_t saveScreenShot(const char* fileName) {
    auto godGuid = EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = nullptr;
    BS->LocateProtocol(&godGuid, nullptr, reinterpret_cast<void**>(&gop));
    const auto screenWidth = gop->Mode->Info->HorizontalResolution;
    const auto screenHeight = gop->Mode->Info->VerticalResolution;
    const auto imgSize = screenWidth * screenHeight;
    const auto imgPixels = new EFI_GRAPHICS_OUTPUT_BLT_PIXEL[imgSize];
    gop->Blt(gop, reinterpret_cast<EFI_GRAPHICS_OUTPUT_BLT_PIXEL*>(imgPixels), EfiBltVideoToBltBuffer, 0, 0, 0, 0, screenWidth, screenHeight, 0);
    // from BGR to ARGB
    for (auto i = 0; i < imgSize; i++) {
        imgPixels[i].Reserved = imgPixels[i].Blue;
        imgPixels[i].Blue = imgPixels[i].Red;
        imgPixels[i].Red = imgPixels[i].Reserved;
        imgPixels[i].Reserved = 0xFF;
    }
    const auto r = lodepng_encode32_file(fileName, reinterpret_cast<uint8_t*>(imgPixels), screenWidth, screenHeight);
    delete[] imgPixels;
    return r;
}
