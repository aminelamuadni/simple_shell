#include "shell.h"

/**
 * get_data - Returns pointer to the shell's data structure.
 *
 * Return: Pointer to the static instance of shell_data_t.
 */
shell_data_t *get_data(void)
{
	static shell_data_t data = {NULL};

	return (&data);
}
