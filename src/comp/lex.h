#pragma once

#include <stddef.h>

struct string {
    size_t start;
    size_t end;
};

struct op {
    char* type;
    size_t pos;
};

struct num {
    long val;
    size_t pos;
};

void lex(const char* script);