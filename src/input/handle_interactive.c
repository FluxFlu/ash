
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

    char cwd[PATH_MAX];
    char displayCwd[128];

    for (;;) {

        getcwd(cwd, PATH_MAX);
        
        int i = 0;
        int f = 0;
        if (cwd[0] == '/' && cwd[1] == 'h' && cwd[2] == 'o' && cwd[3] == 'm' && cwd[4] == 'e' && cwd[5] == '/') {
            i = 6;
            while (cwd[i] != '/' && cwd[i]) {
                i++;
            }
            displayCwd[0] = '~';
            f = 1;
        }
        while (cwd[i]) {
            displayCwd[f] = '/';
            displayCwd[f + 1] = cwd[i + 1];
            f += 2;
            i++;
            while (cwd[i] && cwd[i] != '/') {
                i++;
            }
            if (!cwd[i]) {
                while (cwd[i] != '/') {
                    i--;
                }
                i += 2;
                while (cwd[i]) {
                    displayCwd[f] = cwd[i];
                    i++;
                    f++;
                }
                break;
            }
            if (f >= 128) {
                perror("COMPILER_ERROR[CWD_TOO_LONG]: CWD IS TOO LONG");
            }
        }
        displayCwd[f] = 0;
        state.cwd = displayCwd;
        
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