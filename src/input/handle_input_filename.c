#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

FILE* handleInputFilename(int argc, char** argv) {
    if (argc > 1) {
        struct stat stats;
        if (stat(argv[1], &stats) != 0) {
            switch (errno) {
                case ENOTDIR:
                case ENOENT:
                    fprintf(stderr, "ash: No such file or directory: %s\n", argv[1]);
                    break;
                case EIO:
                    fprintf(stderr, "ash: I/O error while attempting to execute command: %s\n", argv[1]);
                    break;
                case ELOOP:
                    fprintf(stderr, "ash: Too many symlinks (loop assumed) while attempting to execute: %s\n", argv[1]);
                    break;
                case ENAMETOOLONG:
                    fprintf(stderr, "ash: Command name '%s' is too long.\n", argv[1]);
                    break;
                default:
                    fprintf(stderr, "ash: Unable to execute command: %s\n", argv[1]);
            }
            return (FILE*) 1;
        } else if (!(stats.st_mode & R_OK)) {
            fprintf(stderr, "ash: Unknown command. '%s' exists but does not have read permissions.\n", argv[1]);
            return (FILE*) 1;
        }
        return fopen(argv[1], "rx");
    } else {
        return (FILE*) 2;
    }
}