#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>


void printFileErr(int err, char* name) {
    switch (err) {
        case 1:
            fprintf(stderr, "ash: No such file or directory: %s\n", name);
            break;
        case 2:
            fprintf(stderr, "ash: I/O error while attempting to execute command: %s\n", name);
            break;
        case 3:
            fprintf(stderr, "ash: Too many symlinks (loop assumed) while attempting to execute: %s\n", name);
            break;
        case 4:
            fprintf(stderr, "ash: Command name '%s' is too long.\n", name);
            break;
        case -1:
            fprintf(stderr, "ash: Unable to execute command: %s\n", name);
    }
}