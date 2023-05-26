#include "shell.h"

/**
 * interactive - Handles interactive mode of the shell
 */
void interactive(void)
{
	char *buffer;
	size_t size;
	ssize_t line;

	while (1)
	{
		write(1, "$ ", 2);
		line = getline(&buffer, &size, stdin);
		if (line == -1)
		{
			_puts("Failed\n");
			continue;
		}
		if (_strcmp(buffer, EXIT) == 0)
			break;

		/* New variables and for loop */
		char *token;
		char *tokens[10];
		int tokenCount = 0;

		/* Tokenize the input */
		token = strtok(buffer, " \t\n");
		while (token != NULL && tokenCount < 10)
		{
			tokens[tokenCount] = token;
			tokenCount++;
			token = strtok(NULL, " \t\n");
		}

		/* Print the tokens */
		for (int i = 0; i < tokenCount; i++)
		{
			_puts(tokens[i]);
			_puts("\n");
		}
	}

	printf("hi there we are here\n");
}

/**
 * nonInteractive - Handles non-interactive mode of the shell
 */
void nonInteractive(void)
{
	/* TODO: Implement non-interactive mode logic */
}

