#include <termios.h>
#include <stdlib.h>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &state.orig_termios);
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &state.orig_termios) == 1) {
        exit(1);
    }
    atexit(disableRawMode);
    struct termios raw = state.orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |=  (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    // raw.c_lflag |=  (ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}