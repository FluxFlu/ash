

char* delete(size_t* length, size_t* strTop, char* str) {
    (*strTop)--;
    
    for (size_t i = state.pos; i < (*strTop); i++) {
        str[i] = str[i + 1];
    }

    return str;
}