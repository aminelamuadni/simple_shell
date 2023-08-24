/**
 * execute_command - Executes a given command.
 * @cmd: The command to execute.
 * @args: The arguments for the command.
 * @argv: Argument vector from main for error reporting.
 * @cmd: command to execute.
 * @args: arguments for the commands.
 * @argv: Argument vector from the main for errors reporting.
 */
void execute_command(char *cmd, char **args, char *argv[])
{
	pid_t child_pid;
	int status;
	shell_data_t *data = get_data();
	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
		{
			perror(argv[0]);
			free(data->line);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
