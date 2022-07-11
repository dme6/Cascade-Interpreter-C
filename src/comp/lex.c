#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "lex.h"

static size_t isolate_strings(const char* script, struct string** strings) {

    size_t strings_size = 0;

    const char* quote = script;
    while((quote = strchr(quote, '"')) != 0) {

        // TODO: Don't realloc every time.
        // TODO: Handle escape characters.
        *strings = realloc(*strings, (strings_size + 1) * sizeof(struct string));
        strings_size++;

        (*strings)[strings_size - 1].start = quote - script;
        quote = strchr(quote + 1, '"');
        (*strings)[strings_size - 1].end = quote - script;

        quote++;
    }

    return strings_size;
}

static int in_strings(size_t pos, const struct string* strings, size_t strings_size) {

    for(int i = 0; i < strings_size; i++) {
        if(pos > strings[i].start && pos < strings[i].end) {
            return 1;
        }
    }

    return 0;
}

static size_t isolate_ops(const char* script, const struct string* strings, size_t strings_size, struct op** ops) {

    size_t ops_size = 0;

    char* op_types[] = {"=", "+", "-", "*", "/", "==", "!=", ">", "<", ">=", "<="};
    
    for(int i = 0; i < sizeof(op_types) / sizeof(op_types[0]); i++) {

        const char* op_str = script;
        while((op_str = strstr(op_str, op_types[i])) != 0) {

            size_t pos = op_str - script;         

            if(!in_strings(pos, strings, strings_size)) {

                *ops = realloc(*ops, (ops_size + 1) * sizeof(struct op));
                ops_size++;

                (*ops)[ops_size - 1].type = op_types[i];
                (*ops)[ops_size - 1].pos = pos;
            }

            op_str += strlen(op_types[i]);
        }
    }

    return ops_size;
}

static size_t isolate_nums(const char* script, const struct string* strings, size_t strings_size, struct num** nums) {

    size_t nums_size = 0;

    const char* c = script;
    while(*c) {

        size_t pos = c - script;

        if((isdigit(*c) || (*c == '-' && isdigit(*(c + 1)))) && !in_strings(pos, strings, strings_size) && !isalpha(*(c - 1))) {

            *nums = realloc(*nums, (nums_size + 1) * sizeof(struct num));
            nums_size++;
            (*nums)[nums_size - 1].pos = pos;
            (*nums)[nums_size - 1].val = strtol(c, (char**) &c, 10); // Strtol shouldn't modify the pointee of EndPtr.
        } else {
            c++;
        }
    }

    return nums_size;
}

void lex(const char* script) {

    struct string* strings = 0;
    size_t strings_size = isolate_strings(script, &strings);

    puts("Strings:");
    for(int i = 0; i < strings_size; i++) {
        printf("Start: %I64d\tEnd: %I64d\n", strings[0].start, strings[0].end);
    }

    struct op* ops = 0;
    size_t ops_size = isolate_ops(script, strings, strings_size, &ops);

    puts("Ops: ");
    for(int i = 0; i < ops_size; i++) {
        printf("Type: %s\tPos: %I64d\n", ops[i].type, ops[i].pos);
    }

    struct num* nums = 0;
    size_t nums_size = isolate_nums(script, strings, strings_size, &nums);

    for(int i = 0; i < nums_size; i++) {
        printf("Val: %ld\tPos: %I64d\n", nums[i].val, nums[i].pos);
    }

    free(strings);
    free(ops);
    free(nums);
}