//
// Created by o0kam1 on 25-4-13.
//

#include <efi.h>
#include "print.h"

// #include <algorithm>

#include "utils.h"
#include "modules/BaseModule.h"

#include <cstring>
#include <cstdio>
#include <wchar.h>

void printLogo(const char** logo, const int32_t attribute, int* logoX, int* logoY, int* logoWidth, int* logoHeight) {
    const auto startAttribute = getTextColor();
    setTextColor(attribute);
    int line = 0;
    int maxWidth = 0;
    int startX, startY;
    int x, y;
    getCursorPosition(&startX, &startY);
    while (logo[line] != nullptr) {
        getCursorPosition(&x, &y);
        setCursorPosition(startX, y);
        const auto logoLine = logo[line];
        // maxWidth = std::max(maxWidth, static_cast<int>(strlen(logoLine)));
#define max(a, b) ((a) > (b) ? (a) : (b))
        maxWidth = max(maxWidth, strlen(logoLine));
#undef max
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
            printf("%s\n", module->items[j].value);
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
    int startX, startY;
    getCursorPosition(&startX, &startY);
    int x, y;
#define BLOCK L"███"
    setTextColor(EFI_BLACK | EFI_BACKGROUND_BLACK);
    fputws(BLOCK, stdout);
    setTextColor(EFI_RED | EFI_BACKGROUND_RED);
    fputws(BLOCK, stdout);
    setTextColor(EFI_GREEN | EFI_BACKGROUND_GREEN);
    fputws(BLOCK, stdout);
    setTextColor(EFI_BROWN | EFI_BACKGROUND_BROWN);
    fputws(BLOCK, stdout);
    setTextColor(EFI_BLUE | EFI_BACKGROUND_BLUE);
    fputws(BLOCK, stdout);
    setTextColor(EFI_MAGENTA | EFI_BACKGROUND_MAGENTA);
    fputws(BLOCK, stdout);
    setTextColor(EFI_CYAN | EFI_BACKGROUND_CYAN);
    fputws(BLOCK, stdout);
    setTextColor(EFI_LIGHTGRAY | EFI_BACKGROUND_LIGHTGRAY);
    fputws(BLOCK, stdout);
    setTextColor(startAttribute);
    printf("\n");
    getCursorPosition(&x, &y);
    setCursorPosition(startX, y);
    setTextColor(EFI_DARKGRAY | EFI_BACKGROUND_BLACK);
    fputws(BLOCK, stdout);
    setTextColor(EFI_LIGHTRED | EFI_BACKGROUND_RED);
    fputws(BLOCK, stdout);
    setTextColor(EFI_LIGHTGREEN | EFI_BACKGROUND_GREEN);
    fputws(BLOCK, stdout);
    setTextColor(EFI_YELLOW | EFI_BACKGROUND_BROWN);
    fputws(BLOCK, stdout);
    setTextColor(EFI_LIGHTBLUE | EFI_BACKGROUND_BLUE);
    fputws(BLOCK, stdout);
    setTextColor(EFI_LIGHTMAGENTA | EFI_BACKGROUND_MAGENTA);
    fputws(BLOCK, stdout);
    setTextColor(EFI_LIGHTCYAN | EFI_BACKGROUND_LIGHTGRAY);
    fputws(BLOCK, stdout);
    setTextColor(EFI_WHITE | EFI_BACKGROUND_LIGHTGRAY);
    fputws(BLOCK, stdout);
    setTextColor(startAttribute);
    printf("\n");
#undef BLOCK
    *colorsX = startX;
    *colorsY = y - 2;
    *colorsWidth = 3 * 8;
    *colorsHeight = 2;
   setTextColor(startAttribute);
}
