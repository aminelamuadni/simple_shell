#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_ARGS 64

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
void print_prompt(void);
void print_environment(void);
char **tokenize_input(char *line);
ssize_t read_input(char **line, size_t *len);
int execute_command(char *cmd, char **args, char *argv[]);
int is_interactive(void);
char *get_cmd_path(char *cmd);

char *_strcat(char *dest, const char *src);
int _strstart(char *str, char *substr);
size_t _strlen(const char *s);
char *_strchr(const char *s, int c);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);

#endif /* SHELL_H */
