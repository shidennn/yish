#include "../include/executor.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int executeCommand(ParsedCommand* cmd) {
    if (cmd == NULL || cmd->argc == 0 || cmd->args == NULL || cmd->args[0] == NULL) {
        fprintf(stderr, "Error: Invalid command structure.\n");
        return -1;
    }

    pid_t pid = fork();
    if (pid == -1){
        perror("fork");
        return -1;
    }

    else if (pid == 0) {
        // child process
        execvp(cmd->args[0], cmd->args);
        // If execvp returns, it must have failed
        perror("execvp");
        exit(EXIT_FAILURE);

    }

    else {
        // parent process
        int status;
        pid_t result;
        do {
            result = waitpid(pid, &status, 0);
        } while (result == -1 && errno == EINTR);

        if (result == -1) {
            perror("waitpid");
            return -1;
        }
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}