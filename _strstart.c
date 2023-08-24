#include "shell.h"

/**
 * _strstart - Check if a string starts with a given substring.
 * @str: The original string.
 * @substr: The substring.
 *
 * Return: 1 if str starts with substr, 0 otherwise.
 */
int _strstart(char *str, char *substr)
{
	while (*str && *substr)
	{
		if (*str != *substr)
			return (0);
		str++;
		substr++;
	}

	return ((*substr == '\0') ? 1 : 0);
}
