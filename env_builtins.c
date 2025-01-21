#include "shell.h"

/**
 * _setenv - Set or modify an environment variable
 * @variable: Name of the variable
 * @value: Value to set
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *variable, char *value)
{
    int i, var_count = 0;
    char *new_env, **new_environ;

    if (!variable || !value)
        return (-1);

    /* Count current environment variables */
    for (i = 0; environ[i]; i++)
        var_count++;

    /* Create new environment string */
    new_env = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!new_env)
        return (-1);
    _strcpy(new_env, variable);
    _strcat(new_env, "=");
    _strcat(new_env, value);

    /* Create new environment array */
    new_environ = malloc(sizeof(char *) * (var_count + 2));
    if (!new_environ)
    {
        free(new_env);
        return (-1);
    }

    /* Copy and check for existing variable */
    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], variable, _strlen(variable)) == 0 &&
            environ[i][_strlen(variable)] == '=')
        {
            /* Replace existing variable */
            new_environ[i] = new_env;
            continue;
        }
        /* Copy existing variable */
        new_environ[i] = _strdup(environ[i]);
        if (!new_environ[i])
        {
            while (--i >= 0)
                free(new_environ[i]);
            free(new_environ);
            free(new_env);
            return (-1);
        }
    }

    /* Add new variable if it didn't exist */
    if (environ[i] == NULL)
    {
        new_environ[i] = new_env;
        new_environ[i + 1] = NULL;
    }

    /* Free old environment if it was dynamically allocated */
    if (environ != __environ)
    {
        for (i = 0; environ[i]; i++)
            free(environ[i]);
        free(environ);
    }

    environ = new_environ;
    return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @variable: Name of the variable to remove
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(char *variable)
{
    int i, j, var_count = 0;
    char **new_environ;

    if (!variable)
        return (-1);

    /* Count current environment variables */
    for (i = 0; environ[i]; i++)
        var_count++;

    /* Create new environment array */
    new_environ = malloc(sizeof(char *) * var_count);
    if (!new_environ)
        return (-1);

    /* Copy environment excluding the variable to unset */
    for (i = 0, j = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], variable, _strlen(variable)) != 0 ||
            environ[i][_strlen(variable)] != '=')
        {
            new_environ[j] = _strdup(environ[i]);
            if (!new_environ[j])
            {
                while (--j >= 0)
                    free(new_environ[j]);
                free(new_environ);
                return (-1);
            }
            j++;
        }
    }
    new_environ[j] = NULL;

    /* Free old environment if it was dynamically allocated */
    if (environ != __environ)
    {
        for (i = 0; environ[i]; i++)
            free(environ[i]);
        free(environ);
    }

    environ = new_environ;
    return (0);
}

/**
 * handle_setenv - Handles the 'setenv' built-in command
 * @command: The setenv command and its arguments
 * @status: The exit status of the last command
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
 * handle_unsetenv - Handles the 'unsetenv' built-in command
 * @command: The unsetenv command and its arguments
 * @status: The exit status of the last command
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