#include "shell.h"

/**
 * change_dir - Change current directory and update PWD
 * @path: Path to change to
 * Return: 0 on success, -1 on failure
 */
int change_dir(char *path)
{
    char *current_pwd = NULL;
    char buffer[1024];

    /* Get current directory for OLDPWD */
    current_pwd = getcwd(buffer, 1024);
    if (!current_pwd)
        return (-1);

    /* Change directory */
    if (chdir(path) == -1)
        return (-1);

    /* Update PWD and OLDPWD */
    if (_setenv("OLDPWD", current_pwd) == -1)
        return (-1);

    current_pwd = getcwd(buffer, 1024);
    if (!current_pwd)
        return (-1);

    if (_setenv("PWD", current_pwd) == -1)
        return (-1);

    return (0);
}

/**
 * get_oldpwd - Get the OLDPWD environment variable
 * Return: Pointer to OLDPWD value or NULL
 */
char *get_oldpwd(void)
{
    char *oldpwd = _getenv("OLDPWD");

    if (!oldpwd)
        return (NULL);

    return (_strdup(oldpwd));
}

/**
 * handle_cd - Handle the cd command
 * @command: The command and its arguments
 * @status: Pointer to status variable
 */
void handle_cd(char **command, int *status)
{
    char *dir = command[1];
    char *oldpwd = NULL;

    /* If no argument is given, change to HOME directory */
    if (!dir)
    {
        dir = _getenv("HOME");
        if (!dir)
        {
            write(STDERR_FILENO, "cd: No HOME directory\n", 21);
            *status = 1;
            freearray2D(command);
            return;
        }
    }
    /* Handle cd - (change to previous directory) */
    else if (_strcmp(dir, "-") == 0)
    {
        oldpwd = get_oldpwd();
        if (!oldpwd)
        {
            write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
            *status = 1;
            freearray2D(command);
            return;
        }
        dir = oldpwd;
        write(STDOUT_FILENO, dir, _strlen(dir));
        write(STDOUT_FILENO, "\n", 1);
    }

    /* Change directory */
    if (change_dir(dir) == -1)
    {
        write(STDERR_FILENO, command[0], _strlen(command[0]));
        write(STDERR_FILENO, ": can't cd to ", 13);
        write(STDERR_FILENO, dir, _strlen(dir));
        write(STDERR_FILENO, "\n", 1);
        *status = 1;
        free(oldpwd);
        freearray2D(command);
        return;
    }

    free(oldpwd);
    *status = 0;
    freearray2D(command);
}