#include <string.h>
#include <stdio.h>

void (*print)(char* str, size_t size);

void printInteractive(char* str, size_t size) {
    char* new = (char*) realloc(state.writeBuf, state.writeBufLen + size);
    
    if (new == NULL) return;

    memcpy(&new[state.writeBufLen], str, size);
    state.writeBuf = new;
    state.writeBufLen += size;
}

void printNonInteractive(char* str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        putchar(str[i]);
    }
}

void printLit(char* str) {
    print(str, strlen(str));
}

void drawRaw() {
    write(STDOUT_FILENO, state.writeBuf, state.writeBufLen);
    state.writeBufLen = 0;
}


void prompt() {
    printLit(state.username);
    printLit("@");
    printLit(state.hostname);
    printLit(" ");
    
    printLit(state.cwd);

    printLit("> ");
}

void draw(char* str, size_t length) {
    // Update the cursor position
    size_t caretLen = strlen(state.hostname) + strlen(state.username) + strlen("@ _ > ");

    printLit("\x1b[0G");
    printLit("\x1b[K");

    prompt();

    // printLit(state.username);
    // printLit("@");
    // printLit(state.hostname);
    // printLit(" _ > ");
    print(str, length);

    if (length > state.pos) {
        char buf[32];
        snprintf(buf, sizeof(buf), "\x1b[%dD", length - state.pos);
        printLit(buf);
    }

    write(STDOUT_FILENO, state.writeBuf, state.writeBufLen);
    state.writeBufLen = 0;
    // printLit("\x1b[0G");
}