#include <termios.h>
#include <stdbool.h>

typedef struct line {
    char* str;
    size_t strTop;
    size_t length;
} Line;

struct editorState {
    char* hostname;
    char* username;
    char* cwd;

    Line* history;
    unsigned char historyIndex;
    unsigned char historySize;

    bool isInteractive;

    int lastResult;
    char lastResultBuf[3];

    bool color;

    int pos;
    char* line;

    char* writeBuf;
    size_t writeBufLen;

    struct termios orig_termios;
};

struct editorState state;