

char* backspace(size_t* length, size_t* strTop, char* str) {
    if (state.pos == 0) {
        return str;
    }

    (*strTop)--;
    
    for (size_t i = state.pos - 1; i < (*strTop); i++) {
        str[i] = str[i + 1];
    }

    state.pos--;

    return str;
}