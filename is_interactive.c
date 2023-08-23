#include "shell.h"

/**
 * is_interactive - Checks if the shell is running in interactive mode.
 * Return: 1 if interactive, 0 otherwise.
 */
int is_interactive(void)
{
	return (isatty(STDIN_FILENO));
}
