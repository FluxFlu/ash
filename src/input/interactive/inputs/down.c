

char* down(size_t* length, size_t* strTop, char* str) {
    if (state.historyIndex != 0)
        state.historyIndex--;

    if (state.historyIndex == 0) {
        if (!*strTop) {
            return str;
        } else {
            state.pos = 0;
            *strTop = 0;
            *length = 16;
            return (char*) malloc(charSize * 16);
        }
    }

    str = state.history[state.historyIndex - 1].str;
    *strTop = state.history[state.historyIndex - 1].strTop;
    *length = state.history[state.historyIndex - 1].length;

    state.pos = *strTop;

    return str;
}