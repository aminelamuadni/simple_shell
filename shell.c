#include "shell.h"

/**
 * handle_read_input_failure - Handles failures of reading input.
 * @data: The shell data containing the current input line.
 */
static void handle_read_input_failure(shell_data_t *data)
{
	if (is_interactive())
		write(STDOUT_FILENO, "\n", 1);

	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}

	exit(EXIT_SUCCESS);
}

/**
 * process_input_line - Processes each input line and executes the command.
 * @line: The current input line.
 * @argv: Argument vector for error reporting.
 */
static void process_input_line(char *line, char *argv[])
{
	char **args = tokenize_input(line);

	if (args[0] && args[0][0])
		execute_command(args[0], args, argv);
}

/**
 * cleanup_after_execution - Cleans up memory after executing a command.
 * @data: The shell data containing the current input line.
 */
static void cleanup_after_execution(shell_data_t *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
}

/**
 * main - Entry point for the simple shell.
 * @argc: Argument count (not used).
 * @argv: Argument vector, used for error reporting.
 * Return: Always 0 (success).
 */
int main(int argc, char *argv[])
{
	shell_data_t *data = get_data();
	size_t len = 0;
	ssize_t nread;
	(void) argc;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		print_prompt();
		nread = read_input(&data->line, &len);

		if (nread == -1)
			handle_read_input_failure(data);

		data->line[nread - 1] = '\0';
		process_input_line(data->line, argv);
		cleanup_after_execution(data);
	}

	cleanup_after_execution(data);
	return (0);
}
