#include "shell.h"

/**
 * handle_read_input_failure - Handles failures of reading input.
 * @data: The shell data containing the current input line.
 * @last_status: The last known status to exit with in case of a read failure.
 */
static void handle_read_input_failure(shell_data_t *data, int last_status)
{
	if (is_interactive())
		write(STDOUT_FILENO, "\n", 1);

	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}

	exit(last_status);
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
 * is_valid_num - checks if the given string is a valid number.
 * @s: string to check.
 * Return: 1 if string is a valid number, otherwise 0.
 */
int is_valid_num(char *s)
{
	if (*s == '-')
	{
		s++;
	}

	while (*s)
	{
		if (*s < '0' || *s > '9')
		{
			return (0);
		}
		s++;
	}
	return (1);
}

/**
 * process_input_line - Processes each input line and executes the command.
 * @line: The current input line.
 * @argv: Argument vector for error reportingi.
 * Return: The status of the last executed command.
 */
static int process_input_line(char *line, char *argv[])
{
	char **args = tokenize_input(line);
	static int last_status;

	if (args[0])
	{
		if (_strcmp(args[0], "exit") == 0)
		{
			if (args[1])
			{
				last_status = _atoi(args[1]);

				if (!is_valid_num(args[1]) || last_status < 0)
				{
					write(2, argv[0], _strlen(argv[0]));
					write(2, ": 1: ", 5);
					write(2, args[0], _strlen(args[0]));
					write(2, ": Illegal number: ", 18);
					write(2, args[1], _strlen(args[1]));
					write(2, "\n", 1);

					last_status = 2;
				}
			}

			cleanup_after_execution(get_data());
			exit(last_status);
		}
		else if (_strcmp(args[0], "env") == 0)
		{
			print_environment();
		}
		else if (args[0][0])
		{
			last_status = execute_command(args[0], args, argv);
		}
	}

	return (last_status);
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
	int last_status = 0;
	(void) argc;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		print_prompt();
		nread = read_input(&data->line, &len);

		if (nread == -1)
			handle_read_input_failure(data, last_status);

		data->line[nread - 1] = '\0';
		last_status = process_input_line(data->line, argv);
		cleanup_after_execution(data);
	}

	cleanup_after_execution(data);
	return (0);
}
