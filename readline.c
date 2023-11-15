#include "shell.h"

/**
 * read_line - Read a line of input from the user.
 *
 * Return: A pointer to the read line.
 */

char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n;

	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "$ ", 2);

	n = getline(&line, &len, stdin);

	if (n == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
