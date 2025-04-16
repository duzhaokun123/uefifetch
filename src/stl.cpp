//
// Created by o0kam1 on 25-4-11.
//

#ifndef CPP_HPP
#define CPP_HPP

#include <uefi.h>

void* operator new(const size_t size) {
    return malloc(size);
}

void* operator new[](const size_t size) {
    return malloc(size);
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete(void* ptr, size_t) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr, size_t) noexcept {
    free(ptr);
}

#endif //CPP_HPP
