#include "shell.h"

char **tokenizer(char *line);

int main(int ac, char **argv)
{
	char *line = NULL, **command = NULL;
	int status = 0;
	(void)ac;

	while (1)
	{
		line = read_line();
		/* handle the "end of file" condition (Ctrl+D) */
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}

		command = tokenizer(line);
		if (!command)
			continue;

		status = _execute(command, argv);
	}
}
