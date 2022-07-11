#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "lex.h"
#include "lex_utils.h"

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

static size_t isolate_keys(const char* script, const struct string* strings, size_t strings_size, struct key** keys) {

    size_t keys_size = 0;

    char* key_targets[] = {"=", "+", "-", "*", "/", "==", "!=", ">", "<", ">=", "<=", // Operators
                           "var", "if", "else", "while"                            }; // Keywords
    
    for(int i = 0; i < sizeof(key_targets) / sizeof(key_targets[0]); i++) {

        const char* key_str = script;
        while((key_str = strstr(key_str, key_targets[i])) != 0) {

            size_t pos = key_str - script;         

            if(!in_string(pos, strings, strings_size)) {

                *keys = realloc(*keys, (keys_size + 1) * sizeof(struct key));
                keys_size++;

                (*keys)[keys_size - 1].type = key_targets[i];
                (*keys)[keys_size - 1].pos = pos;
            }

            key_str += strlen(key_targets[i]);
        }
    }

    return keys_size;
}

static size_t isolate_nums(const char* script, const struct string* strings, size_t strings_size, struct num** nums) {

    size_t nums_size = 0;

    const char* c = script;
    while(*c) {

        size_t pos = c - script;

        if((isdigit(*c) || (*c == '-' && isdigit(*(c + 1)))) && !in_string(pos, strings, strings_size) && !isalpha(*(c - 1))) {

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

static size_t isolate_vars() {

    size_t vars_size = 0;

    return vars_size;
}

void lex(const char* script) {

    struct string* strings = 0;
    size_t strings_size = isolate_strings(script, &strings);

    puts("Strings:");
    for(int i = 0; i < strings_size; i++) {
        printf("Start: %I64d   End: %I64d\n", strings[0].start, strings[0].end);
    }

    struct key* keys = 0;
    size_t keys_size = isolate_keys(script, strings, strings_size, &keys);

    puts("Keys: ");
    for(int i = 0; i < keys_size; i++) {
        printf("Type: %s   Pos: %I64d\n", keys[i].type, keys[i].pos);
    }

    struct num* nums = 0;
    size_t nums_size = isolate_nums(script, strings, strings_size, &nums);

    puts("Nums: ");
    for(int i = 0; i < nums_size; i++) {
        printf("Val: %ld   Pos: %I64d\n", nums[i].val, nums[i].pos);
    }

    free(strings);
    free(keys);
    free(nums);
}