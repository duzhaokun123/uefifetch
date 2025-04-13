//
// Created by o0kam1 on 25-4-12.
//

#include <uefi.h>
#include "Locale.h"

Locale::Locale() : BaseModule() {
    uintn_t size;
    const auto locale = reinterpret_cast<char*>(getenv("PlatformLang", &size));
    const auto localeItem = ModuleItem{"Locale", locale};

    itemCount = 1;
    items = new ModuleItem[itemCount];
    items[0] = localeItem;
}

Locale::~Locale() {
    delete items;
}

