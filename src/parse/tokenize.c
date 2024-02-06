#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

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
            size_t s = 0;
            size_t f = 0;

            while (i + f < fileString.length && !isspace(file[i + f])) {

                if (file[i + f] == '~' && isspace(file[i + f - 1]) && (file[i + f + 1] == '/' || isspace(file[i + f + 1]) || i + f + 1 >= fileString.length)) {
                    if (state.username == NULL) {
                        char* username = (char*) malloc(LOGIN_NAME_MAX);
                        getlogin_r(username, LOGIN_NAME_MAX);
                        state.username = username;
                    }
                    int len = strlen(state.username) + 6;

                    int n = 0;
                    while (n < len) {
                        if (n <= 5) {
                            str[s + n] = "/home/"[n];
                        } else {
                            str[s + n] = state.username[n - 6];
                        }
                        n++;
                    }
                    s += len;
                    f++;
                    continue;
                }
                str[s] = file[i + f];
                s++;
                f++;
            }

            i += f - 1;

            char* strCpy = malloc(charSize * (s + 1));
            strCpy[s] = 0;
            for (f = 0; f < s; f++) {
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