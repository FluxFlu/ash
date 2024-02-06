

char* up(size_t* length, size_t* strTop, char* str) {
    if (state.historyIndex >= 127 || state.historyIndex >= state.historySize) {
        return str;
    }

    state.historyIndex++;

    if (state.historyIndex == 1) {
        if (*strTop) {
            state.historyIndex++;
            historyShiftUp();
            state.history[0] = (Line){ str, *strTop, *length };
        } else {
            free(str);
        }
    }

    str = state.history[state.historyIndex - 1].str;
    *strTop = state.history[state.historyIndex - 1].strTop;
    *length = state.history[state.historyIndex - 1].length;

    state.pos = *strTop;

    return str;
}