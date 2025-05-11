//
// Created by o0kam1 on 25-4-12.
//

#include "Locale.h"
#include <cstdlib>

Locale::Locale() : BaseModule() {
    const auto locale = getenv("PlatformLang");
    const auto localeItem = ModuleItem{"Locale", locale};

    itemCount = 1;
    items = new ModuleItem[itemCount];
    items[0] = localeItem;
}

Locale::~Locale() {
    delete items;
}

