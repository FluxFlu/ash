#include <termios.h>
#include <stdbool.h>

struct editorState {
    char* hostname;
    char* username;
    char* cwd;

    bool color;

    int pos;
    char* line;

    char* writeBuf;
    size_t writeBufLen;

    struct termios orig_termios;
};

struct editorState state;