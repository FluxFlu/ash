

#define isNull(token) (token.type == SEPARATOR || token.type == NULLTYPE)

#include "../../util/fileExists.c"

#include "./help.c"
#include "./echo.c"
#include "./exit.c"
#include "./cd.c"

char *builtin_str[] = {
    "help",
    "echo",
    "exit",
    "cd",
    NULL,
};

int (*builtin_fn[]) (Token*) = {
    &ash_help,
    &ash_echo,
    &ash_exit,
    &ash_cd,
};