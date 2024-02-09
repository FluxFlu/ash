#include <stdio.h>
#include <stdlib.h>

#include "./utils/history_shift_up.c"

#include "./inputs/input_char.c"
#include "./inputs/delete.c"
#include "./inputs/up.c"
#include "./inputs/down.c"
#include "./inputs/delete_previous_word.c"

String getInteractiveInput() {
    size_t length = 16;
    char*  str  = (char*)  malloc(charSize * length);
    size_t strTop = 0;

    for (;;) {
        char c;
        if (read(STDIN_FILENO, &c, 1) != 1) {
            return (String){ strTop, str };
        }
        if (c == 13) {
            state.historyIndex = 0;
            historyShiftUp();
            state.history[0] = (Line){ str, strTop, length };

            printLit("\r\n");
            state.pos = 0;
            drawRaw();
            return (String){ strTop, str };
        }
        if (iscntrl(c)) {
            char ctrl;
            if (c == 4) {
                if (strTop == 0) {
                    exit(0);
                } else if (state.pos != strTop) {
                    str = delete(&length, &strTop, str);
                }
            } else if (c == 127) {
                // Backspace
                if (state.pos) {
                    state.pos--;
                    str = delete(&length, &strTop, str);
                }
            } else if (c == 27) {
                read(STDIN_FILENO, &ctrl, 1);
                if (ctrl == '[') {
                    read(STDIN_FILENO, &ctrl, 1);
                    switch (ctrl) {
                        case 'A':
                        case 'a':
                            str = up(&length, &strTop, str);
                            break;
                        case 'B':
                        case 'b':
                            str = down(&length, &strTop, str);
                            break;
                        case 'C':
                        case 'c':
                            // Right
                            if (state.pos < strTop)
                                state.pos++;
                            break;
                        case 'D':
                        case 'd':
                            // Left
                            if (state.pos)
                                state.pos--;
                            break;
                        case 'H':
                        case 'h':
                            // Home
                            state.pos = 0;
                            break;
                        case 'F':
                        case 'f':
                            // End
                            state.pos = strTop;
                            break;
                        case '3':
                            // Delete
                            read(STDIN_FILENO, &ctrl, 1);
                            if (ctrl == '~') {
                                if (state.pos != strTop) {
                                    str = delete(&length, &strTop, str);
                                }
                                break;
                            }
                        default:
                            str = inputChar(&length, &strTop, str, '[');
                            str = inputChar(&length, &strTop, str, ctrl);
                    }
                }
            } else if (c == ('w' & 0x1f) || c == 8) {
                // Ctrl+w, Ctrl+Backspace
                str = deletePreviousWord(&length, &strTop, str);
            }
            draw(str, strTop);
            continue;
        }

        str = inputChar(&length, &strTop, str, c);
        
        draw(str, strTop);
    }
}