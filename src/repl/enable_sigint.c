#include <signal.h>

void exit_termination_handler (int signum) {
    exit(2);
    return;
}

void enableSigint() {
    struct sigaction old_action;
    struct sigaction new_action;

    // Set the "signal action handler" in the new_action struct.
    // This decides what will happen once the signal occurs (instead of the disabled SIGINT behavior)
    new_action.sa_handler = exit_termination_handler;

    // Empty the sa_mask.
    sigemptyset(&new_action.sa_mask);

    // Remove every flag from the new_action struct.
    new_action.sa_flags = 0;

    // Read the old signal associated to SIGINT (ctrl+c)
    sigaction(SIGINT, NULL, &old_action);

    // If the old handler wasn't SIG_IGN (basically checking for null)
    if (old_action.sa_handler != SIG_IGN) {
        // Replace the signal handler of SIGINT with the one described by new_action
        // This means that we have replaced the result of SIGINT
        sigaction(SIGINT, &new_action, NULL);
    }
}