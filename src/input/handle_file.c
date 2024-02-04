
#include "./file/get_file_input.c"

void handleFile(FILE* fptr) {
    String input = getFileInput(fptr);
    Token* tokens = tokenize(input);
    free(input.data);

    if (tokens[0].type == NULLTYPE) {
        return;
    }

    for (Token* tokenOffset = tokens; tokenOffset->type != NULLTYPE;) {
        exec(tokenOffset);
        while (tokenOffset->type != NULLTYPE && tokenOffset->type != SEPARATOR) {
            tokenOffset++;
        }
        tokenOffset++;
        while (tokenOffset->type == SEPARATOR) {
            tokenOffset++;
        }
    }

    for (size_t i = 0; tokens[i].type != NULLTYPE; i++) {
        free(tokens[i].value);
    }
    free(tokens);
}