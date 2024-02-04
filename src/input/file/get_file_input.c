#include <stdio.h>
#include <stdlib.h>

String getFileInput(FILE* file) {
    size_t length = 16;
    char*  str  = (char*)  malloc(charSize * length);
    size_t strIndex = 0;
    for (;;) {
        int c = fgetc(file);
        if (c == EOF || file == stdin && c == '\n') {
            return (String){ strIndex, str };
        }
        str[strIndex] = c;
        strIndex++;
        if (strIndex > length) {
            length *= 4;
            str = (char*) realloc(str, charSize * length);
        }
    }
}