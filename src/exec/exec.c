#include <string.h>

#include "./launch.c"
#include "./print_file_err.c"

#include "./builtins/builtins.h"

void exec(Token* tokens) {
    Token command = tokens[0];

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
            return;
        } else if (!(stats.st_mode & X_OK)) {
            fprintf(stderr, "ash: Unknown command. '%s' exists but does not have execute permissions.\n", command.value);
            return;
        }
    } else {
        int err = fileExists(command.value, &stats);
        if (err) {
            printFileErr(err, command.value);
            return;
        } else if (!(stats.st_mode & X_OK)) {
            fprintf(stderr, "ash: Unknown command. '%s' exists but does not have execute permissions.\n", command.value);
            return;
        }
    }

    launch(command.value, argv);
}