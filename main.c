#include "shell.h"

/**
 * main - Simple Shell main function
 * @ac: Count of Arguments
 * @av: Arguments
 * Return: 0 Always (success)
 */

int main(int ac, char **argv)
{
	char *line = NULL, **command = NULL;
	int status = 0;
	int idx = 0;
	(void)ac;

	while (1)
	{
		line = read_line();
		/* handle the "end of file" condition (Ctrl+D) */
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			return (status);
		}

		idx++;
		command = tokenizer(line);
		if (!command)
			continue;

		if (is_builtin(command[0]))
			handle_builtin(command, argv, &status, idx);
		else
			status = _execute(command, argv, idx);
	}
}
