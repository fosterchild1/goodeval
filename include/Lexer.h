#pragma once

typedef enum {
    // operators
    ADD, SUB, MUL, DIV, EXP,

    // other
    RIGHT_PARANTH, LEFT_PARANTH
} TOKEN_TYPE;

typedef struct {
    char* value;
    TOKEN_TYPE token;
} Token;
