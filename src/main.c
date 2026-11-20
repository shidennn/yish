#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char input[1024];
	while (1)
		{
			printf("yish> ");
			if (fgets(input, sizeof(input), stdin) == NULL)
				break;
			printf("you entered: %s", input);
		}
	return 0;
}

