#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

ssize_t read_input(char **line, size_t *len);
void execute_command(char *cmd, char **args, char *argv[], char *line);
int is_interactive(void);

#endif /* SHELL_H */
