//
// Created by o0kam1 on 25-4-13.
//

#include <uefi.h>
#include "print.h"
#include "utils.h"
#include "modules/BaseModule.h"

void printLogo(const char** logo, const int32_t attribute, int* logoX, int* logoY, int* logoWidth, int* logoHeight) {
    const auto startAttribute = getTextColor();
    setTextColor(attribute);
    auto line = 0;
    auto maxWidth = 0;
    int startX, startY;
    int x, y;
    getCursorPosition(&startX, &startY);
    while (logo[line] != nullptr) {
        getCursorPosition(&x, &y);
        setCursorPosition(startX, y);
        const auto logoLine = logo[line];
        maxWidth = max(maxWidth, strlen(logoLine));
        printf("%s\n", logoLine);
        line++;
    }
    getCursorPosition(&x, &y);
    *logoX = startX;
    *logoY = y - line;
    *logoWidth = maxWidth;
    *logoHeight = line;
    setTextColor(startAttribute);
}

void printItems(const BaseModule** modules, const int labelColor, int* itemsX, int* itemsY, int* itemsWidth, int* itemsHeight) {
    const auto startAttribute = getTextColor();
    const auto startBackground = startAttribute & 0xF0;
    int startX, startY;
    getCursorPosition(&startX, &startY);
    auto line = 0;
    int x, y;
    for (int i = 0; modules[i] != nullptr; i++) {
        const auto module = modules[i];
        for (int j = 0; j < module->itemCount; j++) {
            getCursorPosition(&x, &y);
            setCursorPosition(startX, y);
            setTextColor(labelColor | startBackground);
            printf("%s: ", module->items[j].name);
            setTextColor(startAttribute);
            printf("%s\n", module->items[j].vlue);
            line++;
        }
    }
    getCursorPosition(&x, &y);
    *itemsX = startX;
    *itemsY = y - line;
    *itemsWidth = 0; // FIXME: calculate width
    *itemsHeight = line;
}

void printColors(int* colorsX, int* colorsY, int* colorsWidth, int* colorsHeight) {
    const auto startAttribute = getTextColor();
    const auto startBackground = startAttribute & 0xF0;
    int startX, startY;
    getCursorPosition(&startX, &startY);
    int x, y;
#define BLOCK "███"
    setTextColor(EFI_BLACK | startBackground);
    printf(BLOCK);
    setTextColor(EFI_RED | startBackground);
    printf(BLOCK);
    setTextColor(EFI_GREEN | startBackground);
    printf(BLOCK);
    setTextColor(EFI_BROWN | startBackground);
    printf(BLOCK);
    setTextColor(EFI_BLUE | startBackground);
    printf(BLOCK);
    setTextColor(EFI_MAGENTA | startBackground);
    printf(BLOCK);
    setTextColor(EFI_CYAN | startBackground);
    printf(BLOCK);
    setTextColor(EFI_LIGHTGRAY | startBackground);
    printf(BLOCK);
    printf("\n");
    getCursorPosition(&x, &y);
    setCursorPosition(startX, y);
    setTextColor(EFI_DARKGRAY | startBackground);
    printf(BLOCK);
    setTextColor(EFI_LIGHTRED | startBackground);
    printf(BLOCK);
    setTextColor(EFI_LIGHTGREEN | startBackground);
    printf(BLOCK);
    setTextColor(EFI_YELLOW | startBackground);
    printf(BLOCK);
    setTextColor(EFI_LIGHTBLUE | startBackground);
    printf(BLOCK);
    setTextColor(EFI_LIGHTMAGENTA | startBackground);
    printf(BLOCK);
    setTextColor(EFI_LIGHTCYAN | startBackground);
    printf(BLOCK);
    setTextColor(EFI_WHITE | startBackground);
    printf(BLOCK);
    printf("\n");
#undef BLOCK
    *colorsX = startX;
    *colorsY = y - 2;
    *colorsWidth = 3 * 8;
    *colorsHeight = 2;
   setTextColor(startAttribute);
}
