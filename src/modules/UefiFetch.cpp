//
// Created by o0kam1 on 25-4-16.
//

#include "UefiFetch.h"

UefiFetch::UefiFetch() : BaseModule() {
    itemCount = 1;
    items = new ModuleItem[itemCount];
    items[0] = {"UEFIFetch", "" UEFIFETCH_VERSION " (" UEFIFETCH_ARCH ", " __VERSION__ ")"};
}

UefiFetch::~UefiFetch() {
    delete[] items;
}

