#ifndef PARSER_H
#define PARSER_H

typedef struct{
	char** args;
	int argc;
}ParsedCommand;

void freeParsedCommand(ParsedCommand* cmd);
int parse(char* input, ParsedCommand* cmd);

#endif
