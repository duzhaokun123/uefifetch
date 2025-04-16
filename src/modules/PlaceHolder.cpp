//
// Created by o0kam1 on 25-4-13.
//

#include "PlaceHolder.h"

PlaceHolder::PlaceHolder() : BaseModule() {
    constexpr auto item = ModuleItem{"Place", "Holder"};
    itemCount = 1;
    items = new ModuleItem[itemCount];
    items[0] = item;
}

PlaceHolder::~PlaceHolder() {
    delete items;
}
