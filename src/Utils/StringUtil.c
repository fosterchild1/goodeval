#include <string.h>
#include <Utils/array.h>
#include <Utils/Util.h>

char* String_Sub(const char* str, int startIdx, int endIdx) {
    if (endIdx <= startIdx) return "";

    int len = endIdx - startIdx;
    char* result = xmalloc((len + 1) * sizeof(char));
    strncpy(result, str + startIdx, len);
    result[len] = '\0';

    return result;
}

Array String_Split(const char* str, int strLen, char splitChar) {
    Array splitStr = Array_New(sizeof(char*));

    int lastSeenIdx = 0;
    for (int i = 0; i < strLen; i++) {
        if (str[i] != splitChar) continue;
        char* sub = String_Sub(str, lastSeenIdx, i);
        Array_Insert(&splitStr, sub);
        lastSeenIdx = i;
    }

    return splitStr;
}
