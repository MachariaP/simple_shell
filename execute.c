#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * _execute - Executes a command in a child process.
 * @command: An array of strings representing the command and its arguments.
 * @argv: An array of strings representing the command line arguments.
 * @idx: The index of the command in the input.
 *
 * Return: The exit status of the executed command.
 */
int _execute(char **command, char **argv, int idx)
{
	char *full_cmd;
	pid_t child;
	int status;

	/* Path Resolution */
	full_cmd = _getpath(command[0]);
	if (!full_cmd)
	{
		/* Command not found */
		print_error(argv[0], command[0], idx);
		freearray2D(command);
		return 127;
	}

	/* Forking a Child Process */
	child = fork();
	if (child == -1)
	{
		/* Error in forking */
		perror("fork");
		free(full_cmd);
		freearray2D(command);
		return -1;
	}

	/* Child Process Execution */
	if (child == 0)
	{
		if (execve(full_cmd, command, environ) == -1)
		{
			/* Exit child process on failure */
			perror("execve");
			free(full_cmd);
			freearray2D(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent Process */
		if (waitpid(child, &status, 0) == -1)
		{
			/* Error in waitpid */
			perror("waitpid");
			free(full_cmd);
			freearray2D(command);
			return -1;
		}
	}

	/* Cleanup */
	freearray2D(command);
	free(full_cmd);

	/* Check child process exit status */
	if (WIFEXITED(status))
	{
		return WEXITSTATUS(status);
	}
	else
	{
		perror("Child process did not terminate normally");

		return -1;
	}
}
