#include "shell.h"

/**
 * tokenize_input - Tokenizes the input line based on whitespace.
 * @line: The input line to be tokenize.
 * Return: An array of token (words).
 */
char **tokenize_input(char *line)
{
	static char *args[MAX_ARGS];
	char *token;
	int i = 0;

	token = strtok(line, " ");

	while (token && i < MAX_ARGS - 1)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	args[i] = NULL;
	return (args);
}
