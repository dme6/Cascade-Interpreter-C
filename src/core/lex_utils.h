#pragma once

#include <stddef.h>
#include "lex.h"

#define def_in_text(T) \
int in_##T(size_t pos, const struct T* T##s, size_t T##s_size) { \
    for(int i = 0; i < T##s_size; i++) { \
        if(pos >= T##s[i].base.start && pos <= T##s[i].base.end) { \
            return 1; \
        } \
    } \
    return 0; \
}

def_in_text(string)
def_in_text(key)
def_in_text(num)