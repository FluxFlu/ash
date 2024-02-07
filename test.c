#include <stdio.h>

int main(void) {
    int i = 0;
    while (1) {
        if (i++ > 1000000) {
            printf("[-]");
            i = 0;
        }
    }
}
