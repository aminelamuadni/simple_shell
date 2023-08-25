#include "shell.h"

/**
 * print_environment - Prints the current environment variables.
 */
void print_environment(void)
{
	int index = 0;

	while (environ[index])
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
}
