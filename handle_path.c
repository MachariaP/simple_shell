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

        /* Check if the command includes a '/' */
        for (i = 0; command[i]; i++)
        {
                if (command[i] == '/')
                {
                        if (stat(command, &st) == 0)
                                return (_strdup(command));

                        return (NULL);
                }
        }

        /* Get the PATH environment variable */
        path_env = _getenv("PATH");
        if (!path_env)
                return (NULL);

        /* Iterate through directories in PATH */
        for (dir = strtok(path_env, ":"); dir; dir = strtok(NULL, ":"))
        {
                /* Allocate memory for the full command path */
                full_cmd = malloc(_strlen(dir) + _strlen(command) + 2);
                if (!full_cmd)
                {
                        free(path_env);
                        return (NULL); /* Memory allocation failed */
                }

                /* Construct the full command path */
                _strcpy(full_cmd, dir);
                _strcat(full_cmd, "/");
                _strcat(full_cmd, command);

                /* Check if the full command path exists */
                if (stat(full_cmd, &st) == 0)
                {
                        free(path_env);
                        return (full_cmd); /* Return the full command path */
                }

                /* Free the allocated memory for full_cmd */
                free(full_cmd);
        }

        /* Free the PATH environment variable */
        free(path_env);

        return (NULL); /* Command not found in PATH */
}
