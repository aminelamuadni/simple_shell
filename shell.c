#include "shell.h"

/**
 * get_data - Returns a pointer to the shell's data structure.
 *
 * Return: Pointer to the static instance of shell_data_t.
 */
shell_data_t *get_data(void)
{
	static shell_data_t data = {NULL};

	return (&data);
}

/**
 * read_input - Reads a line from stdin.
 * @line: Pointer to the line buffer.
 * @len: Length of the buffer.
 * Return: Number of characters read.
 */
ssize_t read_input(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}

/**
 * execute_command - Executes a given command.
 * @cmd: The command to execute.
 * @args: The arguments for the command.
 * @argv: Argument vector from main for error reporting.
 */
void execute_command(char *cmd, char **args, char *argv[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * is_interactive - Checks if the shell is running in interactive mode.
 * Return: 1 if interactive, 0 otherwise.
 */
int is_interactive(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * main - Entry point for simple shell.
 * @argc: Argument count (not used).
 * @argv: Argument vector, used for error reporting.
 * Return: Always 0 (success).
 */
int main(int argc, char *argv[])
{
	shell_data_t *data = get_data();
	size_t len = 0;
	ssize_t nread;
	char *args[2];

	(void) argc;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		if (is_interactive())
			write(STDOUT_FILENO, "$ ", 2);

		nread = read_input(&data->line, &len);

		if (nread == -1)
		{
			if (is_interactive())
				write(STDOUT_FILENO, "\n", 1);

			free(data->line);
			exit(EXIT_SUCCESS);
		}

		data->line[nread - 1] = '\0';
		args[0] = data->line;
		args[1] = NULL;

		if (data->line[0])
			execute_command(args[0], args, argv);
	}

	free(data->line);
	return (0);
}
