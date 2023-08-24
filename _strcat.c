#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the resulting string dest.
 */
char *_strcat(char *dest, const char *src)
{
	int i = 0, j = 0;

	while (dest[i])
		i++;

	while (src[j])
		dest[i++] = src[j++];

	dest[i] = '\0';

	return (dest);
}
