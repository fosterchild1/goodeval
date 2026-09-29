#include <stdlib.h>

void* xmalloc(size_t size) {
    void* p = malloc(size);
    if (p == NULL) {
        exit(EXIT_FAILURE);
    }

    return p;
}
