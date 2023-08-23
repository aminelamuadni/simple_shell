#include "shell.h"

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
			exit(0);
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
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *args[2];

	(void) argc;

	while (1)
	{
		printf("#cisfun$ ");

		nread = read_input(&line, &len);

		if (nread == -1)
		{
			printf("\n");
			free(line);
			exit(0);
		}

		line[nread - 1] = '\0';
		args[0] = line;
		args[1] = NULL;

		execute_command(args[0], args, argv);
	}

	free(line);
	return (0);
}
