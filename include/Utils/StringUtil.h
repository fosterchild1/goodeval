#pragma once

#include <Utils/array.h>

char* String_Sub(const char* str, int startIdx, int endIdx);

Array String_Split(const char* str, int strLen, char splitChar);
