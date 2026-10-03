#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Lexer.h"
#include "Utils/array.h"
#include "Utils/StringUtil.h"

char* GetFullNumber(const char* str, int startIdx) {
    const char* p = str + startIdx;

    while (*p != '\0') {
        if (*p < '0' || *p > '9') break;
        p++;
    }
    p--;

    int endIdx = p - str;
    return String_Sub(str, startIdx, endIdx);
}

Token StrToToken(const char* str, int startIdx) {
    char first = str[startIdx];
    
    // numbers
    if (first >= '0' && first <= '9') {
        return (Token){GetFullNumber(str, startIdx), NUM};
    }

    // operators
    char* strFirst = CharToString(first);
    if (first == '+') 
        return (Token){strFirst, ADD};
    else if (first == '-')
        return (Token){strFirst, SUB};
    else if (first == '*')
        return (Token){strFirst, MUL};
    else if (first == '/')
        return (Token){strFirst, DIV};
    else if (first == '^')
        return (Token){strFirst, EXP};

    // misc
    if (first == '(')
        return (Token){strFirst, LEFT_PARANTH};
    else if (first == ')')
        return (Token){strFirst, RIGHT_PARANTH};

    return (Token){NULL, ERR};
}


Array ParseString(const char* str) {
    Array tokens = Array_New(sizeof(Token));
    
    int currIdx = 0;
    while (currIdx < (int)strlen(str)) {
        char currChar = str[currIdx];
        if (currChar == ' ' || currChar == '\n') { currIdx++; continue; }
        
        Token parsedToken = StrToToken(str, currIdx);
        if (parsedToken.token == ERR) exit(EXIT_FAILURE);
        printf("%s", parsedToken.value);
        currIdx += strlen(parsedToken.value);
    }

    return tokens;
}
