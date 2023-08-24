#include "shell.h"

/**
 * get_PATH_var - Fetches the PATH variable from the environment.
 * Return: Pointer to the PATH string or NULL if not found.
 */
static char *get_PATH_var(void)
{
	int index = 0;

	while (environ[index])
	{
		if (_strstart(environ[index], "PATH="))
			return (environ[index] + 5);
		index++;
	}
	return (NULL);
}

/**
 * copy_str - Creates a copy of a given string.
 * @src: The string to copy.
 * Return: A pointer to the copied string or NULL on failure.
 */
static char *copy_str(char *src)
{
	int i;
	int len = _strlen(src);
	char *copy = malloc(len + 1);

	if (!copy)
		return (NULL);

	for (i = 0; i <= len; i++)
		copy[i] = src[i];

	return (copy);
}

/**
 * construct_full_path - Constructs a full path from directory and command.
 * @dir: The directory part.
 * @cmd: The command part.
 * Return: A pointer to the constructed full path or NULL on failure.
 */
static char *construct_full_path(char *dir, char *cmd)
{
	char *full_path = malloc(512);

	if (!full_path)
		return (NULL);
	full_path[0] = '\0';
	_strcat(full_path, dir);
	_strcat(full_path, "/");
	_strcat(full_path, cmd);
	return (full_path);
}

/**
 * check_cmd_in_dir - Checks if a command is executable in a given directory.
 * @dir: The directory to check in.
 * @cmd: The command to look for.
 * Return: 1 if the command is found and executable, 0 otherwise.
 */
static int check_cmd_in_dir(char *dir, char *cmd)
{
	char *full_path = construct_full_path(dir, cmd);

	if (!full_path)
		return (0);

	if (access(full_path, X_OK) == 0)
	{
		free(full_path);
		return (1);
	}

	free(full_path);
	return (0);
}

/**
 * get_cmd_path - Retrieve the path of a command.
 * @cmd: The command to look for in PATH.
 * Return: The full path of the command or NULL if not found.
 */
char *get_cmd_path(char *cmd)
{
	char *PATH_var = get_PATH_var();
	char *PATH_copy, *dir;

	if (!PATH_var)
		return (NULL);

	PATH_copy = copy_str(PATH_var);
	if (!PATH_copy)
		return (NULL);

	dir = strtok(PATH_copy, ":");
	while (dir)
	{
		if (check_cmd_in_dir(dir, cmd))
		{
			char *full_path = construct_full_path(dir, cmd);

			free(PATH_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(PATH_copy);
	return (NULL);
}
