#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeParsedCommand(ParsedCommand* cmd){
    if (cmd == NULL) return;
    for(int i = 0; i < cmd->argc; i++){
        free(cmd->args[i]);
    }
    free(cmd->args);
    cmd->args = NULL;
    cmd->argc = 0;
}

int parse(char* input, ParsedCommand* cmd){
    if (input == NULL || cmd == NULL){
        printf("Invalid input or command structure\n");
        return -1;
    }

    cmd->argc = 0;
    cmd->args = malloc((strlen(input) + 1) * sizeof(char*));
    if (cmd->args == NULL){
        printf("Memory allocation failed\n");
        return -1;
    }

    char* token = strtok(input, " ");
    while(token != NULL){
        cmd->args[cmd->argc] = malloc(strlen(token) + 1);
        if (cmd->args[cmd->argc] == NULL){
            printf("Memory allocation failed\n");
            freeParsedCommand(cmd);
            return -1;
        }
        strcpy(cmd->args[cmd->argc], token);
        cmd->argc++;
        token = strtok(NULL, " ");
    }
    cmd->args[cmd->argc] = NULL;
    return 0;
}



