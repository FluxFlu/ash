
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

        printf("%i", getpid());
        
        if (execvp(file, argv) == -1) {
            fprintf(stderr, "\rash: Unable to exec [%s]\r\n", file);
            perror("ash");
        }
        exit(1);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("ash: Error forking");
    } else {
        // Parent process
        childPid = pid;

        do {
            wpid = waitpid(childPid, &childStatus, WUNTRACED);
            // if (shouldKillProcess) {
            // int childStatus;
            // waitpid(childPid, &childStatus, WNOHANG);
                // kill(childPid, SIGKILL);
            //     kill(childPid, SIGKILL);
            //     if (sig != 0) {
            //         printf("Error: Unable to kill child.");
            //         exit(1);
            //     }
            //     if (WIFEXITED(childStatus) || WIFSIGNALED(childStatus)) {
            //         break;
            //     }
            // waitpid(childPid, &child
            // }
        } while (!WIFEXITED(childStatus) && !WIFSIGNALED(childStatus));
    }

    enableRawMode();

    disableSigint();

    return childStatus;
}