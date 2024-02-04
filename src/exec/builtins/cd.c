

int ash_cd(Token* tokens) {
    if (isNull(tokens[0])) {
        printLit("\r\n");
        return 0;
    } else {
        if (fileExists(tokens[0].value)) {
            return 1;
        }
        if (chdir(tokens[0].value) != 0) {
            printLit("cd: Unable to change dir...\r\n");
        }
    }
    return 0;
}