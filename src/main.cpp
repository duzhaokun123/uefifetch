#include <efi.h>
#include <uefi.h>
#include "utils.h"
#include "modules/Display.h"
#include "modules/Locale.h"
#include "modules/Memory.h"
#include "modules/Shell.h"
#include "modules/UEFI.h"
#include "modules/PlaceHolder.h"
#include "print.h"
#include "logo.h"
#include "modules/IP4.h"

void forModulePrintItem(const BaseModule* module) {
    for (int i = 0; i < module->itemCount; i++) {
        printf("%s: %s\n", module->items[i].name, module->items[i].vlue);
    }
}

int main(int argc, char** argv) {
    const BaseModule* items[] = {
        new UEFI(),
        new Shell(),
        new Display(),
        new Memory(),
        new IP4(),
        new Locale(),
        nullptr
    };

    int x1, y1;
    int x2, y2;
    int logoWidth, logoHeight;
    printLogo(defaultLogo, EFI_LIGHTRED | EFI_BACKGROUND_BLACK, &x1, &y1, &logoWidth, &logoHeight);
    setCursorPosition(x1 + 4 + logoWidth, y1);
    int itemsWidth, itemsHeight;
    printItems(items, EFI_LIGHTRED, &x1, &y1, &itemsWidth, &itemsHeight);
    printf("\n");
    getCursorPosition(&x2, &y2);
    setCursorPosition(x1, y2);
    int colorsWidth, colorsHeight;
    printColors(&x1, &y1, &colorsWidth, &colorsHeight);
    const auto leftHeight = logoHeight;
    const auto rightHeight = itemsHeight + 1 + colorsHeight;
    setCursorPosition(0, y1 + colorsHeight + (leftHeight > rightHeight ? (leftHeight - rightHeight) : 0) + 1);
    printf("\n");

    if (not haveShell()) {
        printf("Press any key to continue...\n");
        waitForKey();
    }

    return 0;
}
