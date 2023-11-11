#include "shell.h"

/**
 * is_positive_number - Checks if a string represents a positive number.
 * @str: The string to check.
 *
 * Return: 1 if the string is a positive number, 0 otherwise.
 */
int is_positive_number(char *str)
{
	int i;

	/* Check if the input string is NULL */
	if (!str)
		return (0);

	/* Iterate through the string to check if each character is a digit */
	for (i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}

/**
 * _atoi - Converts a string to an integer.
 * @str: The string to convert.
 *
 * Return: The integer representation of the string.
 */
int _atoi(char *str)
{
	int i, num = 0;

	/* Iterate through the string to build the integer */
	for (i = 0; str[i]; i++)
	{
		num *= 10;
		num += (str[i] - '0');
	}

	return (num);
}
