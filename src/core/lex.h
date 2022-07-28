#pragma once

#include <stddef.h>

// Common/base struct
struct token {
    size_t start;
    size_t end;
    void (*some_func)(void);
};

struct string {
    struct token base;
};

// Represents any reserved string of characters (like commas, operators, and keywords) 
struct key {
    struct token base;
    char* type;
};

struct num {
    struct token base;
    long val;
};

// Variables include functions and stuff.
struct var {
    struct token base;
};

void lex(const char* script);