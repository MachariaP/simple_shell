#include "shell.h"

/**
 * _setenv - Set or modify an environment variable
 * @variable: Name of the variable
 * @value: Value to set
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *variable, char *value)
{
    int i;
    char *new_env, *env_var;
    size_t new_len;

    if (!variable || !value)
        return (-1);

    /* Create new environment string */
    new_len = _strlen(variable) + _strlen(value) + 2;
    new_env = malloc(new_len);
    if (!new_env)
        return (-1);

    _strcpy(new_env, variable);
    _strcat(new_env, "=");
    _strcat(new_env, value);

    /* Check if variable exists */
    for (i = 0; environ[i]; i++)
    {
        env_var = _strdup(environ[i]);
        if (!env_var)
        {
            free(new_env);
            return (-1);
        }

        if (_strcmp(strtok(env_var, "="), variable) == 0)
        {
            free(env_var);
            environ[i] = new_env;
            return (0);
        }
        free(env_var);
    }

    /* Add new variable */
    environ[i] = new_env;
    environ[i + 1] = NULL;
    return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @variable: Name of the variable to remove
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(char *variable)
{
    int i, j;
    char *env_var;

    if (!variable)
        return (-1);

    for (i = 0; environ[i]; i++)
    {
        env_var = _strdup(environ[i]);
        if (!env_var)
            return (-1);

        if (_strcmp(strtok(env_var, "="), variable) == 0)
        {
            free(env_var);
            /* Shift remaining variables */
            for (j = i; environ[j]; j++)
            {
                environ[j] = environ[j + 1];
            }
            return (0);
        }
        free(env_var);
    }

    return (-1);
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