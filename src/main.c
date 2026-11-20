#include <stdio.h>
#include <stdlib.h>
#include "../include/executor.h"
#include "../include/parser.h"

int main(void)
{
	char input[1024];
	ParsedCommand cmd = {0};
	while (1)
		{
			printf("yish> ");
			if (fgets(input, sizeof(input), stdin) == NULL)
				break;
			//printf("you entered: %s", input);
			if (parse(input, &cmd) == 0)
				{
					executeCommand(&cmd);
				}

			freeParsedCommand(&cmd);
		}
	return 0;
}

