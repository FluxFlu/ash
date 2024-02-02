#include <stdio.h>
#include <stdlib.h>

#define charSize sizeof(char)

char* getInput(FILE* file) {
    size_t length = 16;
    char*  str  = (char*)  malloc(charSize * length);
    size_t strIndex = 0;
    for (;;) {
        int c = fgetc(file);
        if (c == ';' || c == EOF || file == stdin && c == '\n') {
            return str;
        }
        if (c == 0) {
            c == 1;
        }
        str[strIndex] = c;
        strIndex++;
        if (strIndex > length) {
            length *= 4;
            str = (char*) realloc(str, charSize * length);
        }
    }
}