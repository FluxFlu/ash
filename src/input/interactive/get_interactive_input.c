#include <stdio.h>
#include <stdlib.h>

#include "./utils/history_shift_up.c"

#include "./inputs/input_char.c"
#include "./inputs/backspace.c"
#include "./inputs/up.c"
#include "./inputs/down.c"

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

            print("\r\n", 2);
            state.pos = 0;
            drawRaw();
            return (String){ strTop, str };
        }
        if (iscntrl(c)) {
            char ctrl;
            if (c == 127) {
                str = backspace(&length, &strTop, str);
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
                        default:
                            str = inputChar(&length, &strTop, str, '[');
                            str = inputChar(&length, &strTop, str, ctrl);
                    }
                }
            }
            draw(str, strTop);
            continue;
        }

        str = inputChar(&length, &strTop, str, c);
        
        draw(str, strTop);
    }
}