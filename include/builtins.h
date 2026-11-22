#ifndef BUILTINS_H
#define BUILTINS_H
#include "parser.h"

int isBuiltinCommand(ParsedCommand* cmd);
int executeBuiltinCommand(ParsedCommand* cmd);


#endif