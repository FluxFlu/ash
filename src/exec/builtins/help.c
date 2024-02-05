

int ash_help (Token* tokens) {
    printLit("ash ");
    printLit(VERSION);
    printLit("\r\n\n");
    printLit("Built-in commands:\r\n");
    printLit("cd - change directory\r\n");
    printLit("echo - print to the console\r\n");
    printLit("exit - exit the shell\r\n");
    printLit("help - display this help message\r\n");
    return 0;
}