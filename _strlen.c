#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: The string to measure.
 *
 * Return: The length of the string.
 */
size_t _strlen(const char *s)
{
	const char *start = s;

	while (*s)
		s++;

	return (s - start);
}
