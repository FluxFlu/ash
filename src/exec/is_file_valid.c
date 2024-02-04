#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>


bool isFileValid(char* name) {
    struct stat stats;
    if (stat(name, &stats) != 0) {
        switch (errno) {
            case ENOTDIR:
            case ENOENT:
                fprintf(stderr, "ash: No such file or directory: %s\n", name);
                break;
            case EIO:
                fprintf(stderr, "ash: I/O error while attempting to execute command: %s\n", name);
                break;
            case ELOOP:
                fprintf(stderr, "ash: Too many symlinks (loop assumed) while attempting to execute: %s\n", name);
                break;
            case ENAMETOOLONG:
                fprintf(stderr, "ash: Command name '%s' is too long.\n", name);
                break;
            default:
                fprintf(stderr, "ash: Unable to execute command: %s\n", name);
        }
        return 0;
    } else if (!(stats.st_mode & X_OK)) {
        fprintf(stderr, "ash: Unknown command. '%s' exists but does not have execute permissions.\n", name);
        return 0;
    }
    return 1;
}