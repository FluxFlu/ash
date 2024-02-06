
#include <sys/wait.h>

int launch (char* file, char** argv) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
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
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    enableRawMode();

    return WEXITSTATUS(status);
}