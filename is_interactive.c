#include "shell.h"

/**
 * is_interactive - Checks if the simple shell is running in interactive mode.
 * Return: 1 if interactive, 0 if not.
 */
int is_interactive(void)
{
	return (isatty(STDIN_FILENO));
}
