#include <stdio.h>

void prompt() {
    printLit(state.username);
    printLit("@");
    printLit(state.hostname);
    printLit(" _ > ");
}