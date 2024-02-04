
#include <limits.h>

#include "./interactive/get_interactive_input.c"

void handleInteractive() {
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);

    state.hostname = hostname;
    state.username = username;
    
    state.pos = 0;

    enableRawMode();

    printLit("Welcome to Ashley's Shell\r\n");
    printLit("Type `help` for usage information\r\n");

    for (;;) {
        printLit("\x1b[0G");
        prompt();
        drawRaw();

        String input = getInteractiveInput();
        Token* tokens = tokenize(input);
        free(input.data);

        if (tokens[0].type == NULLTYPE) {
            continue;
        }

        for (Token* tokenOffset = tokens; tokenOffset->type != NULLTYPE;) {
            exec(tokenOffset);
            while (tokenOffset->type != NULLTYPE && tokenOffset->type != SEPARATOR) {
                tokenOffset++;
            }
            if (tokenOffset->type == NULLTYPE) {
                break;
            }
            tokenOffset++;
            while (tokenOffset->type == SEPARATOR) {
                tokenOffset++;
            }
        }

        for (size_t i = 0; tokens[i].type != NULLTYPE; i++) {
            free(tokens[i].value);
        }
        free(tokens);
    }
}