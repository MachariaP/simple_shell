#include "shell.h"

/**
 * tokenizer - Tokenizes a string into an array of strings.
 * @line: The string to tokenize.
 *
 * Return: An array of strings (tokens), or NULL on failure.
 */
char **tokenizer(char *line)
{
	char *token = NULL, *tmp = NULL;
	char **command = NULL;
	int cpt = 0, i = 0;

	/* Check if the input string is NULL */
	if (!line)
		return (NULL);

	/* Duplicate the input line to avoid modification */
	tmp = _strdup(line);

	/* Tokenize the duplicated line */
	token = strtok(tmp, DELIM);

	/* Handle the case when there are no tokens */
	if (token == NULL)
	{
		free(line), tmp = NULL;
		free(tmp), tmp = NULL;
		return (NULL);
	}

	/* Count the number of tokens */
	while (token)
	{
		cpt++;
		token = strtok(NULL, DELIM);
	}

	/* Free the duplicated line */
	free(tmp);
	tmp = NULL;

	/* Allocate memory for the array of strings (command) */
	command = malloc(sizeof(char *) * (cpt + 1));
	if (!command)
	{
		free(line);
		return (NULL);
	}

	/* Tokenize the original line and store tokens in the command array */
	token = strtok(line, DELIM);
	while (token)
	{
		command[i] = _strdup(token);
		token = strtok(NULL, DELIM);
		i++;
	}

	/* Set the last element of the command array to NULL */
	command[i] = NULL;

	/* Free the original line */
	free(line);

	return (command);
}
