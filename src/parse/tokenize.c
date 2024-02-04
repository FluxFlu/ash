#include <ctype.h>
#include <stdlib.h>

Token* tokenize(String fileString) {
    char* file = fileString.data;
    char* str = (char*) malloc(charSize * 128);
    size_t strLen = charSize * 128;

    Token* tokens = (Token*) malloc(tokenSize * 64);
    size_t tokenIndex = 0;
    size_t tokenArraySize = tokenSize * 64;

    size_t i = 0;
    for (; i < fileString.length; i++) {
        if (file[i] == '"' || file[i] == '\'') {
            char toEnd = file[i];

            size_t j = 0;
            i++;
            for (;;) {
                if (file[i + j] == '\\') {
                    i++;
                    str[j] = file[i + j];
                    j++;
                    continue;
                }
                if (i + j >= fileString.length) {
                    fprintf(stderr, "ash: Unexpected end of file. Quotes are not balanced...");
                    exit(1);
                }
                if (file[i + j] == toEnd) {
                    break;
                }
                str[j] = file[i + j];
                j++;
                if (j >= strLen) {
                    strLen *= 2;
                    str = (char*) realloc(str, strLen);
                }
            }
            i += j;

            char* strCpy = malloc(charSize * (j + 1));
            strCpy[j] = 0;
            for (size_t f = 0; f < j; f++) {
                strCpy[f] = str[f];
            }

            tokens[tokenIndex].type = STRING;
            tokens[tokenIndex].value = strCpy;
            tokenIndex++;
            if (tokenIndex * tokenSize >= tokenArraySize) {
                tokenArraySize *= 2;
                tokens = (Token*) realloc(tokens, tokenArraySize);
            }
        } else if (file[i] == '\n' || file[i] == '\r' || file[i] == ';') {
            tokens[tokenIndex].type = SEPARATOR;
            tokens[tokenIndex].value = NULL;

            tokenIndex++;
            if (tokenIndex * tokenSize >= tokenArraySize) {
                tokenArraySize *= 2;
                tokens = (Token*) realloc(tokens, tokenArraySize);
            }
        } else if (!isspace(file[i])) {
            size_t j = 0;
            while (i + j < fileString.length && !isspace(file[i + j])) {
                str[j] = file[i + j];
                j++;
            }

            i += j - 1;

            char* strCpy = malloc(charSize * (j + 1));
            strCpy[j] = 0;
            for (size_t f = 0; f < j; f++) {
                strCpy[f] = str[f];
            }

            tokens[tokenIndex].type = IDENTIFIER;
            tokens[tokenIndex].value = strCpy;
            tokenIndex++;
            if (tokenIndex * tokenSize >= tokenArraySize) {
                tokenArraySize *= 2;
                tokens = (Token*) realloc(tokens, tokenArraySize);
            }
        }
    }
    tokens[tokenIndex].type = NULLTYPE;
    tokens[tokenIndex].value = NULL;
    free(str);
    return tokens;
}