#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include "../include/builtins.h"
#include "../include/parser.h"
#include "../include/shell.h"
#include "../include/executor.h"


void startShell() {
    char* input = NULL;
    size_t inputSize = 0;
    ssize_t length;
    ParsedCommand cmd = {0};

    while (1) {
        printf("yish> ");
        //getline returns the number of characters read, including the newline(\n) character, or -1 on failure or EOF.
        length = getline(&input, &inputSize, stdin); 
        if (length == -1) {
            if (feof(stdin)){
                break;
            }
            perror("getline");
            break; // Exit on EOF or error
        }
        

        if (parse(input, &cmd) == 0) {
            if (cmd.argc == 0) {
                // No command entered
                freeParsedCommand(&cmd);
                continue;
            }
            //fprintf(stderr, "Command: %s\n", cmd.args[0]);
            //fprintf(stderr, "Is builtin: %d\n", isBuiltinCommand(&cmd));
            if (isBuiltinCommand(&cmd)) {
                int result = executeBuiltinCommand(&cmd);
                if (result == 1) {
                    break; // Exit the shell
                } else if (result == -1) {
                    fprintf(stderr, "Error executing built-in command.\n");
                }
            } 
            else {
                executeCommand(&cmd);
            }
            
        }
        
        freeParsedCommand(&cmd);
    }

    free(input);
}