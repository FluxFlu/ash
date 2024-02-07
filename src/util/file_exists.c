#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

int fileExists(char* filename, struct stat* stats) {
    if (stat(filename, stats) != 0) {
        switch (errno) {
            case ENOTDIR:
            case ENOENT:
                return 1;
            case EIO:
                return 2;
            case ELOOP:
                return 3;
            case ENAMETOOLONG:
                return 4;
            default:
                return -1;
        }
    }
    return 0;
}