#include "shell.h"
#include <stddef.h>
#include <unistd.h>

/**
 * set_env - Implements the setenv built-in command.
 * @command: The setenv command and its arguments.
 * @status: The exit status of the last command.
 */
void set_env(char **command, int *status)
{
    if (command[1] == NULL || command[2] == NULL || command[3] != NULL)
    {
        write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 28);
        (*status) = 2;
        return;
    }

    if (setenv(command[1], command[2], 1) == -1)
    {
        perror("setenv");
        (*status) = 2;
    }
}

/**
 * unset_env - Implements the unsetenv built-in command.
 * @command: The unsetenv command and its arguments.
 * @status: The exit status of the last command.
 */
void unset_env(char **command, int *status)
{
    if (command[1] == NULL || command[2] != NULL)
    {
        write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 26);
        (*status) = 2;
        return;
    }

    if (unsetenv(command[1]) == -1)
    {
        perror("unsetenv");
        (*status) = 2;
    }
}