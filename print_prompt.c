#include "shell.h"

/**
 * print_prompt - Print the shell prompt if in interactive mode.
 */
void print_prompt(void)
{
	if (is_interactive())
		write(STDOUT_FILENO, "$ ", 2);
}
