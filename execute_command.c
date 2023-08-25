#include "shell.h"

/**
 * handle_relative_path_cmd - Determines the full path for commands.
 * @cmd: The command to check.
 * Return: The full path or the command itself if it's a relative path.
 */
static char *handle_relative_path_cmd(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.' || _strchr(cmd, '/'))
		return (cmd);
	return (get_cmd_path(cmd));
}

/**
 * error_command_not_found - Reports an error when the command is not found.
 * @cmd: The command that was not found.
 * @argv: Argument vector from main for the error reporting.
 * Return: Error status indicating the command is not found (127).
 */
static int error_command_not_found(char *cmd, char *argv[])
{
	shell_data_t *data = get_data();

	write(2, argv[0], _strlen(argv[0]));
	write(2, ": 1: ", 5);
	write(2, cmd, strlen(cmd));
	write(2, ": not found\n", 12);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	return (127);
}

/**
 * handle_exec_error - Handles errors during execve execution.
 * @argv: Argument vector from main for error reporting.
 * Return: Error status indicating execution failure (typically EXIT_FAILURE).
 */
static int handle_exec_error(char *argv[])
{
	shell_data_t *data = get_data();

	perror(argv[0]);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	return (EXIT_FAILURE);
}

/**
 * execute_command - Executes a given command.
 * @cmd: The command to execute.
 * @args: The arguments for the command.
 * @argv: Argument vector from main for error reporting.
 * Return: The exit status of the executed command or error code.
 */
int execute_command(char *cmd, char **args, char *argv[])
{
	pid_t child_pid;
	int status;
	char *full_path = handle_relative_path_cmd(cmd);

	if (!full_path)
		return (error_command_not_found(cmd, argv));

	if (access(full_path, X_OK) == -1)
	{
		perror(argv[0]);
		if (full_path != cmd)
			free(full_path);
		return (126);
	}

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			handle_exec_error(argv);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = 1;
	}

	if (full_path != cmd)
		free(full_path);

	return (status);
}
