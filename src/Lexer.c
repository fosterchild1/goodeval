#include <string.h>
#include <Lexer.h>
#include <Utils/array.h>
#include <Utils/StringUtil.h>

Array ParseString(char* str) {
    Array tokens = Array_New(sizeof(Token));

    Array splitStr = String_Split(str, strlen(str), ' ');
    char** splitData = (char**)splitStr.data;

    for (int i = 0; i < splitStr.len; i++) {
        char* expr = splitData[i];
    }

    return tokens;
}
