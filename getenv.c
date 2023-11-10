#include "shell.h"

/**
 * _getenv - Retrieves the value of an environment variable.
 * @variable: The name of the environment variable.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(char *variable)
{
    char *tmp, *key, *value, *env;
    int i;

    /* Iterate through the environment variables */
    for (i = 0; environ[i]; i++)
    {
        /* Duplicate the current environment variable for tokenization */
        tmp = _strdup(environ[i]);

        /* Tokenize the key (variable name) from the environment variable */
        key = strtok(tmp, "=");

        /* Check if the current environment variable's key matches the target variable */
        if (_strcmp(key, variable) == 0)
        {
            /* Tokenize the value of the environment variable */
            value = strtok(NULL, "\n");

            /* Duplicate the value for return */
            env = _strdup(value);

            /* Free the duplicated environment variable and return the result */
            free(tmp);
            return (env);
        }

        /* Free the duplicated environment variable */
        free(tmp), tmp = NULL;
    }

    /* Return NULL if the variable is not found in the environment */
    return (NULL);
}
