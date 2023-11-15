#include "shell.h"

/**
 * _getpath - Resolves the full path of a command.
 * @command: The command to resolve.
 *
 * Return: A dynamically allocated string representing the full path,
 *         or NULL if the command is not found or encounters an error.
 */

char *_getpath(char *command)
{
    char *path_env, *full_cmd, *dir;
    int i;
    struct stat st;

    /* if the command is already path */
    for (i = 0; command[i]; i++)
    {
        if (command[i] == '/')
        {
            /* if path exists */
            if (stat(command, &st) == 0)
                return (_strdup(command));

            return (NULL);
        }
    }

    /* if the user unset path */
    path_env = _getenv("PATH");
    if (!path_env)
        return (NULL);

    /* Handling path */
    dir = strtok(path_env, ":");

    while (dir)
    {
        /* size = len(directory) + len(command) + 2 ('/' and '\0')*/
        full_cmd = malloc(_strlen(dir) + _strlen(command) + 2);
        if (full_cmd)
        {
            _strcpy(full_cmd, dir);
            _strcat(full_cmd, "/");
            _strcat(full_cmd, command);
            if (stat(full_cmd, &st) == 0)
            {
                free(path_env);
                return (full_cmd);
            }
            free(full_cmd), full_cmd = NULL;

            dir = strtok(NULL, ":");
        }
    }
    free(path_env);
    return (NULL);
}