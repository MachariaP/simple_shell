#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define DELIM "\t\n"
extern char **environ;

/* tokenizer.c */
char **tokenize_line(char *line);

/* input_line.c */
char *read_line(void);

/* execute.c */
int _execute(char **command, char **argv);

/* string.c */
char *string_duplicate(const char *str);
int string_compare(char *s1, char *s2);
int string_length(char *s);
char *string_concatenate(char *destination, char *source);
char *string_copy(char *destination, char *source);

/* utils.c */
void free_2D_array(char **arr);

#endif /* SHELL_H */

