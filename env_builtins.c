#include "shell.h"

/**
 * _setenv - Set or modify an environment variable
 * @variable: Name of the variable
 * @value: Value to set
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *variable, char *value)
{
    char *env_var;
    int len;

    if (!variable || !value)
        return (-1);

    len = _strlen(variable) + _strlen(value) + 2;
    env_var = malloc(len);
    if (!env_var)
        return (-1);

    _strcpy(env_var, variable);
    _strcat(env_var, "=");
    _strcat(env_var, value);

    if (putenv(env_var) == -1)
    {
        free(env_var);
        return (-1);
    }

    return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @variable: Name of the variable to remove
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(char *variable)
{
    if (!variable)
        return (-1);

    if (unsetenv(variable) == -1)
        return (-1);

    return (0);
}

/**
 * handle_setenv - Handles the 'setenv' built-in command.
 * @command: The setenv command and its arguments.
 * @status: The exit status of the last command.
 */
void handle_setenv(char **command, int *status)
{
    if (!command[1] || !command[2] || command[3])
    {
        write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 28);
        *status = 1;
        freearray2D(command);
        return;
    }

    if (_setenv(command[1], command[2]) == -1)
    {
        write(STDERR_FILENO, "setenv: failed to set variable\n", 30);
        *status = 1;
        freearray2D(command);
        return;
    }

    *status = 0;
    freearray2D(command);
}

/**
 * handle_unsetenv - Handles the 'unsetenv' built-in command.
 * @command: The unsetenv command and its arguments.
 * @status: The exit status of the last command.
 */
void handle_unsetenv(char **command, int *status)
{
    if (!command[1] || command[2])
    {
        write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 24);
        *status = 1;
        freearray2D(command);
        return;
    }

    if (_unsetenv(command[1]) == -1)
    {
        write(STDERR_FILENO, "unsetenv: failed to unset variable\n", 34);
        *status = 1;
        freearray2D(command);
        return;
    }

    *status = 0;
    freearray2D(command);
}