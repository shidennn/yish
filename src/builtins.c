#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/builtins.h"

int isBuiltinCommand(ParsedCommand* cmd) {
    if (cmd == NULL || cmd->argc == 0 || cmd->args == NULL || cmd->args[0] == NULL) {
        return 0; // Not a built-in command
    }

    const char* builtins[] = {"cd", "exit", NULL};
    for (int i = 0; builtins[i] != NULL; i++) {
        if (strcmp(cmd->args[0], builtins[i]) == 0) {
            return 1; // It's a built-in command
        }
    }
    return 0; // Not a built-in command
    
}

int executeBuiltinCommand(ParsedCommand* cmd) {
    if (cmd == NULL || cmd->argc == 0 || cmd->args == NULL || cmd->args[0] == NULL) {
        fprintf(stderr, "Error: Invalid command structure.\n");
        return -1;
    }

    if (strcmp(cmd->args[0], "cd") == 0) {
        if (cmd->argc == 1) {
            const char* homePath = getenv("HOME");

            if (homePath == NULL) {
                fprintf(stderr, "Error: HOME environment variable not set.\n");
                return -1;
            }
            if (chdir(homePath) != 0) {
                perror("cd");
                return -1;
            }
        }
        else if (cmd->argc == 2) {
            if (chdir(cmd->args[1]) != 0) {
                perror("cd");
                return -1;
            }
            
        }
        else {
        fprintf(stderr, "Usage: cd [directory]\n");
        return -1;
    }
        return 0; // Success
    }

    if (strcmp(cmd->args[0], "exit") == 0) {
        if (cmd->argc == 1){
            return 1;
        }
        else {
            fprintf(stderr, "Error: 'exit' command does not take any arguments.\n");
            return -1;
        }
    }
    

    fprintf(stderr, "Error: Unknown built-in command '%s'\n", cmd->args[0]);
    return -1; // Unknown built-in command

}