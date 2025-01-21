#include "shell.h"

/**
 * change_dir - Change current directory and update PWD
 * @path: Path to change to
 * Return: 0 on success, -1 on failure
 */
int change_dir(char *path)
{
    char current_dir[1024];
    char *old_pwd;

    /* Get the current directory before changing */
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        return (-1);

    /* Try to change directory */
    if (chdir(path) == -1)
        return (-1);

    /* Update OLDPWD */
    old_pwd = _strdup(current_dir);
    if (old_pwd)
    {
        _setenv("OLDPWD", old_pwd);
        free(old_pwd);
    }

    /* Update PWD */
    if (getcwd(current_dir, sizeof(current_dir)) != NULL)
        _setenv("PWD", current_dir);

    return (0);
}

/**
 * handle_cd - Handle the cd command
 * @command: The command and its arguments
 * @status: Pointer to status variable
 */
void handle_cd(char **command, int *status)
{
    char *dir = NULL;
    char *oldpwd;

    if (!command[1] || _strcmp(command[1], "~") == 0)
    {
        dir = _getenv("HOME");
        if (!dir)
        {
            write(STDERR_FILENO, "cd: HOME not set\n", 16);
            *status = 1;
            return;
        }
    }
    else if (_strcmp(command[1], "-") == 0)
    {
        oldpwd = _getenv("OLDPWD");
        if (!oldpwd)
        {
            write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
            *status = 1;
            return;
        }
        dir = oldpwd;
        write(STDOUT_FILENO, dir, _strlen(dir));
        write(STDOUT_FILENO, "\n", 1);
    }
    else
        dir = command[1];

    if (change_dir(dir) == -1)
    {
        write(STDERR_FILENO, command[0], _strlen(command[0]));
        write(STDERR_FILENO, ": can't cd to ", 13);
        write(STDERR_FILENO, dir, _strlen(dir));
        write(STDERR_FILENO, "\n", 1);
        *status = 1;
    }
    else
        *status = 0;

    freearray2D(command);
}