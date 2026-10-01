#pragma once

#include <Utils/array.h>

typedef enum {
    ERR,

    // values
    NUM, IDENTIFIER,

    // operators
    ADD, SUB, MUL, DIV, EXP,

    // other
    RIGHT_PARANTH, LEFT_PARANTH
} TOKEN_TYPE;

typedef struct {
    char* value;
    TOKEN_TYPE token;
} Token;

Array ParseString(const char* str);
