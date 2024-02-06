

void historyShiftUp() {
    if (state.historySize < 127) {
        state.historySize++;
    }
    for (char f = state.historySize - 2; f >= 0; f--) {
        if (f == 127) {
            free(state.history[f].str);
        } else {
            state.history[f + 1] = state.history[f];
        }
    }
}