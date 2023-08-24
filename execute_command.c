#include "shell.h"

/**
 * execute_command - Executes a given command.
 * @cmd: The command to execute.
 * @args: The arguments for the command.
 * @argv: Argument vector from main for error reporting.
 */
void execute_command(char *cmd, char **args, char *argv[])
{
	shell_data_t *data = get_data();

	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
	char full_path[1024];

	snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);

	if (access(full_path, X_OK) == 0)
	{
	pid_t child_pid = fork();

		if (child_pid == 0)
		{
		execve(full_path, args, environ);
		perror(argv[0]);
		free(data->line);
		free(path_copy);
		exit(EXIT_FAILURE);
		}
		else
		{
		wait(NULL);
		free(path_copy);
		return;
			}
		}
	dir = strtok(NULL, ":");
	}

	fprintf(stderr, "%s: command not found\n", cmd);
	free(path_copy);
}

