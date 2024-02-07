
void setLastResult(char* str, int size) {
    size = 7 - size;
    for (int i = 0; i < 7; i++) {
        if (i >= size) {
            state.lastResultBuf[i] = str[i - size];
        } else {
            state.lastResultBuf[i] = 0;
        }
    }
}