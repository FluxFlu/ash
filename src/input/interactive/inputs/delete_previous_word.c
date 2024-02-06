
char* deletePreviousWord(size_t* length, size_t* strTop, char* str) {

    if (state.pos == 0) {
        return str;
    }

    size_t toMoveCount = 0;

    // If the top is stacked with slashes, just remove all of them
    if (state.pos >= 2 && str[state.pos - 1] == '/' && str[state.pos - 2] == '/') {
        while (state.pos && str[state.pos - 1] == '/') {
            state.pos--;
            (*strTop)--;
            toMoveCount++;
        }
    } else if (state.pos) {
        if (str[state.pos - 1] == '/') {
            state.pos--;
            (*strTop)--;
            toMoveCount++;
        }

        while (state.pos && str[state.pos - 1] == ' ') {
            state.pos--;
            (*strTop)--;
            toMoveCount++;
        }

        while (state.pos && str[state.pos - 1] != '/' && str[state.pos - 1] != ' ') {
            state.pos--;
            (*strTop)--;
            toMoveCount++;
        }
    }

    if (toMoveCount && *strTop != state.pos) {
        char* toRef   = str + state.pos;
        char* fromRef = str + state.pos + toMoveCount;
        for (size_t i = 0; i < *strTop; i++) {
            toRef[i] = fromRef[i];
        }
    }
    return str;
}