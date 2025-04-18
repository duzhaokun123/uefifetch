#include <efi.h>
#include <lodepng.h>
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
#include "screenshot.h"
#include "modules/SMBIOS.h"
#include "modules/FS.h"
#include "modules/FS2.h"
#include "modules/IP4.h"
#include "modules/UefiFetch.h"
#include <cargs.h>

static struct cag_option options[]{
    {
        .identifier = 'S',
        .access_letters = nullptr,
        .access_name = "no-screenshot",
        .description = "Do not take a screenshot",
    },
    {
        .identifier = 's',
        .access_letters = nullptr,
        .access_name = "screenshot",
        .value_name = "PATH",
        .description = "Save screenshot to PATH (default: uefifetch.png)",
    },
    {
        .identifier = 'v',
        .access_letters = "v",
        .access_name = "version",
        .description = "Show version information",
    },
    {
        .identifier = 'h',
        .access_letters = "h",
        .access_name = "help",
        .description = "Show this help message",
    }
};

int main(const int argc, char** argv) {
    bool noScreenshot = false;
    auto screenshotPath = "uefifetch.png";

    cag_option_context optionContext;
    cag_option_init(&optionContext, options, CAG_ARRAY_SIZE(options), argc, argv);
    while (cag_option_fetch(&optionContext)) {
        switch (cag_option_get_identifier(&optionContext)) {
            case 'S': {
                noScreenshot = true;
                break;
            }
            case 's': {
                screenshotPath = cag_option_get_value(&optionContext);
                break;
            }
            case 'v': {
                printf("uefifetch\n");
                printf("%s\n", argv[0]);
                printf("%s (%s, %s)\n", UEFIFETCH_VERSION, UEFIFETCH_ARCH, __VERSION__);
                return EFI_SUCCESS;
            }
            case 'h': {
                printf("Usage: %s [OPTION]\n", argv[0]);
                printf("\n");
                printf("OPTION:\n");
                cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
                return EFI_SUCCESS;
            }
            case '?': {
                cag_option_print_error(&optionContext, stdout);
                break;
            }
            default: ;
        }
    }

    const BaseModule* items[] = {
        new UEFI(),
        new SMBIOS(),
        new Shell(),
        new Display(),
        new Memory(),
        new FS(),
        new FS2(),
        new IP4(),
        new Locale(),
        new UefiFetch(),
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

    if (not noScreenshot) {
        printf("Save screenshot to %s...", screenshotPath);
        const auto r = saveScreenShot(screenshotPath);
        if (r == 0) {
            printf("OK\n");
        } else {
            printf("Failed (%s)\n", lodepng_error_text(r));
        }
    }

    if (not haveShell()) {
        printf("Press any key to continue...\n");
        waitForKey();
    }

    return 0;
}
