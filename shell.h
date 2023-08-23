#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * struct shell_data - Data structure for the shell.
 * @line: The input line read from stdin.
 */
typedef struct shell_data
{
	char *line;
} shell_data_t;

extern char **environ;

shell_data_t *get_data(void);
void handle_sigint(int sig);
ssize_t read_input(char **line, size_t *len);
void execute_command(char *cmd, char **args, char *argv[]);
int is_interactive(void);

#endif /* SHELL_H */
