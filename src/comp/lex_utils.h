#pragma once

#include <stddef.h>
#include "lex.h"

int in_string(size_t pos, const struct string* strings, size_t strings_size);