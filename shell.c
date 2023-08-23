#include "shell.h"

/**
 * main - Entry point for the simple shell.
 * @argc: Argument count (not used).
 * @argv: Argument vector, used for the  error reporting.
 * Return: Always 0 (success).
 */
int main(int argc, char *argv[])
{
	shell_data_t *data = get_data();
	size_t len = 0;
	ssize_t nread;
	char **args;
	(void) argc;
	signal(SIGINT, handle_sigint);
	while (1)
	{
		print_prompt();

		nread = read_input(&data->line, &len);

		if (nread == -1)
		{
			if (is_interactive())
				write(STDOUT_FILENO, "\n", 1);
			free(data->line);
			exit(EXIT_SUCCESS);
		}

		data->line[nread - 1] = '\0';
		args = tokenize_input(data->line);
		if (args[0] && args[0][0])
			execute_command(args[0], args, argv);
		free(data->line);
		data->line = NULL;
	}

	free(data->line);
	return (0);
}
