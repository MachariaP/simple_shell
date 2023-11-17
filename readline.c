#include "shell.h"

#define INITIAL_LINE_BUFFER_SIZE 1024

/**
 * read_line - Read a line of input from the user.
 *
 * Return: A pointer to the read line.
 */
char *read_line(void)
{
    char *line = NULL; /* Buffer to store the input line */
    size_t len = 0;    /* Length of the input line */
    ssize_t n;         /* Number of characters read */

    if (isatty(STDIN_FILENO) == 1)
    {
        const char *prompt = "$ ";
        write(STDOUT_FILENO, prompt, _strlen(prompt));
    }

    /* Allocate memory for the initial line buffer */
    line = malloc(INITIAL_LINE_BUFFER_SIZE);
    if (line == NULL)
    {
        perror("malloc");
        return NULL;
    }

    /* Read a line from the standard input */
    n = getline(&line, &len, stdin);

    /* Check if an error or end-of-file occurred during input */
    if (n == -1)
    {
        perror("getline");
        free(line);    /* Free the allocated memory for the line */
        return NULL;   /* Return NULL to indicate an error or EOF */
    }
    else if (n == 0)
    {
        free(line);    /* Free the allocated memory for the line */
        return NULL;   /* Return NULL to indicate end-of-file (Ctrl+D) */
    }

    return line; /* Return the pointer to the read line */
}
