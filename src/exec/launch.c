
#include <sys/wait.h>

#include "../repl/enable_sigint.c"

pid_t childPid;

#include "../repl/disable_sigint.c"

int launch (char* file, char** argv) {
    pid_t pid, wpid;
    int childStatus;

    pid = fork();
    if (pid == 0) {
        // Child process
        enableSigint();
        disableRawMode();

        if (execvp(file, argv) == -1) {
            fprintf(stderr, "\rash: Unable to exec [%s]\r\n", file);
            perror("ash");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("ash: Error forking");
    } else {
        // Parent process
        childPid = pid;

        do {
            wpid = waitpid(childPid, &childStatus, WUNTRACED);
        } while (!WIFEXITED(childStatus) && !WIFSIGNALED(childStatus));
    }

    enableRawMode();

    disableSigint();

    return childStatus;
}