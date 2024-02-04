#include <termios.h>

struct editorState {
    char* hostname;
    char* username;
    char* cwd;

    int pos;
    char* line;

    char* writeBuf;
    size_t writeBufLen;

    struct termios orig_termios;
};

struct editorState state;