#include "shell.h"

/**
 * handle_sigint - Signal handler function for cleanup.
 * @sig: The signal number.
 * Return: Nothing.
 */
void handle_sigint(int sig)
{
	shell_data_t *data = get_data();

	(void)sig;

	if (is_interactive())
		write(STDOUT_FILENO, "\n", 1);

	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}

	exit(EXIT_SUCCESS);
}
