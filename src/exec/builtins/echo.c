

int ash_echo (Token* tokens) {
    if (isNull(tokens[0])) {
        printLit("\r\n");
        return 0;
    }

    for (size_t i = 0; !isNull(tokens[i]); i++) {
        printLit(tokens[i].value);
        printLit(" ");
    }
    
    printLit("\r\n");
    return 0;
}