

char* inputChar(size_t* length, size_t* strTop, char* str, char c) {
    (*strTop)++;
    if (*strTop >= *length) {
        (*length) *= 4;
        str = (char*) realloc(str, charSize * *length);
    }
    if (state.pos == *strTop - 1) {
        str[state.pos] = c;
    } else {
        for (size_t i = *strTop; i > state.pos; i--) {
            str[i] = str[i - 1];
        }
        str[state.pos] = c;
    }
    state.pos++;

    return str;
}