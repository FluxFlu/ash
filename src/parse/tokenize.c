
#define charSize sizeof(char)

Token* tokenize(char* file) {
    
    char* str = (char*) malloc(charSize * 128);

    size_t strLen = 128;
    for (size_t i = 0; file[i]; i++) {
        if (file[i] == '"' || file[i] == '\'') {
            char toEnd = file[i];

            size_t j = 0;
            i++;
            for (;;) {
                if (file[i + j] == '\\') {
                    i++;
                    str[j] = file[i + j];
                    continue;
                }
                if (file[i + j] == toEnd) {
                    break;
                }
                str[j] = file[i + j];
                j++;
                if (j >= strLen) {
                    strLen *= 2;
                    str = (char*) realloc(str, charSize * strLen);
                }
            }
            i += j;
            printf("[%i]", j);
        }
    }
}