
#include <sys/wait.h>

int launch (char* file, char** argv) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        disableRawMode();
        if (execvp(file, argv) == -1) {
            fprintf(stderr, "ash: ERROR WITH EXEC: %s\r\n", file);
            perror("ash");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("ash: ERROR FORKING");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    enableRawMode();

    return 1;
}