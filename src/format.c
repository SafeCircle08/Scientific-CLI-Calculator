#include "format.h"

const int FORMAT_SPACE_COUNT = 35;

void format_description(char* dest, size_t size, const char* description) {
    const char* c = description;
    size_t used = 0;

    while (*c && used < size - 2) {
        if (*c == '\n') {
            dest[used++] = '\n';

            for (int i = 0; i < (FORMAT_SPACE_COUNT + 7) && used < size - 2; i++) {
                dest[used++] = ' ';
            }
            c++;
        } else dest[used++] = *c++;
    }
    dest[used++] = '\n';
    dest[used] = '\0';
}