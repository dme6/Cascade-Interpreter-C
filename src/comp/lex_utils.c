#include <stddef.h>
#include "lex.h"

int in_string(size_t pos, const struct string* strings, size_t strings_size) {

    for(int i = 0; i < strings_size; i++) {
        if(pos > strings[i].start && pos < strings[i].end) {
            return 1;
        }
    }

    return 0;
}