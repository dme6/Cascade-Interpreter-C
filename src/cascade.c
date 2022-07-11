#include <stdlib.h>
#include <stdio.h>
#include "../include/cascade.h"
#include "comp/lex.h"

void interpret_file(const char* path) {

    FILE* f = fopen(path, "r");

    fseek(f, 0, SEEK_END);
    size_t f_size = ftell(f);
    rewind(f);

    char* buffer = calloc(f_size + 1, sizeof(char));
    fread(buffer, sizeof(char), f_size, f);

    interpret_string(buffer);

    free(buffer);
}

void interpret_string(const char* script) {

    lex(script);
}