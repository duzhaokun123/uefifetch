//
// Created by o0kam1 on 25-4-12.
//

#ifndef BASE_H
#define BASE_H

typedef struct {
    const char* name;
    const char* value;
} ModuleItem;

class BaseModule {
public:
    int itemCount;
    ModuleItem* items;
};

#endif //BASE_H
