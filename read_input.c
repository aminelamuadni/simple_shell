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
