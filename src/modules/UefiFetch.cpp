//
// Created by o0kam1 on 25-4-16.
//

#include "UefiFetch.h"
#include "version.h"

UefiFetch::UefiFetch() : BaseModule() {
    itemCount = 1;
    items = new ModuleItem[itemCount];
    items[0] = {"UEFIFetch", "" PROJECT_VERSION " (" CMAKE_SYSTEM_PROCESSOR ", " __VERSION__ ")"};
}

UefiFetch::~UefiFetch() {
    delete[] items;
}

