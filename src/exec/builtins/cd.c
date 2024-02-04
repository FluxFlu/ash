

int ash_cd(Token* tokens) {
    if (isNull(tokens[0])) {
        size_t len = HOST_NAME_MAX + 6;
        char buffer[len + 1];
        size_t i = 0;
        while (i < len) {
            if (i <= 5) {
                buffer[i] = "/home/"[i];
            } else {
                buffer[i] = state.username[i - 6];
            }
            i++;
        }
        buffer[i] = 0;
        if (chdir(buffer) != 0) {
            printLit("cd: Unable to change dir...\r\n");
        }
        return 0;
    } else {
        struct stat stats;
        int err = fileExists(tokens[0].value, &stats);
        if (err) {
            if (err == 1) {
                printLit("cd: Directory ");
                printLit(tokens[0].value);
                printLit(" does not exist...\r\n");
            } else {
                printLit("cd: Unable to access dir\r\n");
            }
            return 1;
        } else if (!S_ISDIR(stats.st_mode)) {
            printLit("cd: File ");
            printLit(tokens[0].value);
            printLit(" is not a directory...\r\n");
        } else if (chdir(tokens[0].value) != 0) {
            printLit("cd: Unable to change dir...\r\n");
        }
    }
    return 0;
}