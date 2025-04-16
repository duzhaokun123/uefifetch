//
// Created by o0kam1 on 25-4-13.
//

#ifndef PRINT_H
#define PRINT_H
#include "modules/BaseModule.h"

void printLogo(const char** logo, int32_t attribute, int* logoX, int* logoY, int* logoWidth, int* logoHeight);

void printItems(const BaseModule** modules, int labelColor, int* itemsX, int* itemsY, int* itemsWidth, int* itemsHeight);

void printColors(int* colorsX, int* colorsY, int* colorsWidth, int* colorsHeight);

#endif //PRINT_H
