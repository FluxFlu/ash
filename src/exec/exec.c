#include <string.h>

#include "../repl/set_last_result.c"

bool wasSigint = false;

#include "./launch.c"
#include "./print_file_err.c"
#include "../repl/print_signal.c"

#include "./builtins/builtins.h"


void exec(Token* tokens) {
    Token command = tokens[0];

    wasSigint = false;

    if (isNull(command)) {
        return;
    }

    size_t i = 0;
    if (command.value[0] != '.' && command.value[0] != '/' && command.value[0] != '~') {
        while (builtin_str[i] != NULL) {
            if (strcmp(builtin_str[i], command.value) == 0) {
                builtin_fn[i](tokens + 1);
                return;
            }
            i++;
        }
    }

    char** argv = (char**) malloc(ptrSize * 64);
    size_t argvSize = ptrSize * 64;
    i = 0;
    while (tokens[i].type != NULLTYPE) {
        argv[i] = tokens[i].value;
        i++;
        if ((i + 1) * ptrSize >= argvSize) {
            argvSize *= 2;
            argv = (char**) realloc(argv, argvSize);
        }
    }
    argv[i] = 0;

    struct stat stats;

    if (command.value[0] != '.' && command.value[0] != '/' && command.value[0] != '~') {
        char glob[strlen(command.value) + strlen("/usr/bin/") + 1];
        strncpy(glob, "/usr/bin/", 9);
        strncpy(glob + 9, command.value, strlen(command.value) + 1);

        int err = fileExists(glob, &stats);
        if (err) {
            printFileErr(err, command.value);
            state.lastResult = 127;
            setLastResult("127", 3);
            return;
        } else if (!(stats.st_mode & X_OK)) {
            fprintf(stderr, "ash: Unknown command. '%s' exists but does not have execute permissions.\n", command.value);
            return;
        }
    } else {
        int err = fileExists(command.value, &stats);
        if (err) {
            printFileErr(err, command.value);
            state.lastResult = 127;
            setLastResult("127", 3);
            return;
        } else if (!(stats.st_mode & X_OK)) {
            fprintf(stderr, "ash: Unknown command. '%s' exists but does not have execute permissions.\n", command.value);
            return;
        }
    }

    int result = launch(command.value, argv);

    char lastChar;
    if (state.writeBufLen) {
        lastChar = state.writeBuf[state.writeBufLen - 1];
    } else {
        lastChar = state.lastCharWritten;
    }

    // if (lastChar != '\n' && lastChar != '\r') {
    //     printLit("\r\n");
    // }

    if (wasSigint) {
        state.lastResult = 2;
        setLastResult("SIGINT", 6);
        return;
    }

    if (state.isInteractive) {
        if (WIFSIGNALED(result)) {
            int sig = WTERMSIG(result);
            if (sig == SIGINT) {
                setLastResult("SIGINT", 6);
                return;
            }
        
            // printf("|%i /= %i|", sig, SIGINT);
            printSignal(sig);
            drawRaw();
            exit(1);
        }

        result = WEXITSTATUS(result);
        state.lastResultBuf[0] = 0;
        state.lastResultBuf[1] = 0;
        state.lastResultBuf[2] = 0;
        state.lastResultBuf[3] = 0;
        state.lastResult = result;
        state.lastResultBuf[6] = result % 10 + 48;
        result /= 10;
        if (result) {
            state.lastResultBuf[5] = result % 10 + 48;
            result /= 10;
            if (result) {
                state.lastResultBuf[4] = result % 10 + 48;
            } else {
                state.lastResultBuf[4] = 0;
            }
        } else {
            state.lastResultBuf[5] = 0;
            state.lastResultBuf[4] = 0;
        }
    }
}