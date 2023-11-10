#include "shell.h"

/**
 * freearray2D - Frees a 2D array of strings.
 * @arr: The 2D array to be freed.
 */
void freearray2D(char **arr)
{
	int i;

	/* Check if the input array is NULL */
	if (!arr)
		return;

	/* Iterate through the array to free each string and then free the array */
	for (i = 0; arr[i]; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}

	free(arr);
	arr = NULL;
}

/**
 * print_error - Prints an error message to standard error.
 * @name: The name of the program.
 * @cmd: The command causing the error.
 * @idx: The index of the command in the input.
 */
void print_error(char *name, char *cmd, int idx)
{
	char *index;
	char mssg[] = ": not found\n";

	index = _itoa(idx);

	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, index, _strlen(index));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, mssg, _strlen(mssg));

	free(index);
}

/**
 * _itoa - Converts an integer to a string.
 * @n: The integer to be converted.
 *
 * Return: The string representation of the integer.
 */
char *_itoa(int n)
{
	char buffer[20];
	int i = 0;

	/* Handle the case when the integer is 0 */
	if (n == 0)
		buffer[i++] = '0';
	else
	{
		/* Convert the integer to a string */
		while (n > 0)
		{
			buffer[i++] = (n % 10) + '0';
			n /= 10;
		}
	}

	buffer[i] = '\0';
	reverse_string(buffer, i);

	return (_strdup(buffer));
}

/**
 * convert_to_string - Converts an integer to a string.
 * @n: The integer to be converted.
 *
 * Return: The string representation of the integer.
 */
char *convert_to_string(int n)
{
	char buffer[20];
	int i = 0;

	/* Handle the case when the integer is 0 */
	if (n == 0)
		buffer[i++] = '0';
	else
	{
		/* Convert the integer to a string */
		while (n > 0)
		{
			buffer[i++] = (n % 10) + '0';
			n /= 10;
		}
	}

	buffer[i] = '\0';
	reverse_string(buffer, i);

	return _strdup(buffer);
}

/**
 * reverse_string - Reverses a string in place.
 * @str: The string to be reversed.
 * @len: The length of the string.
 */
void reverse_string(char *str, int len)
{
	char tmp;
	int start = 0;
	int end = len - 1;

	/* Swap characters from the start and end until they meet in the middle */
	while (start < end)
	{
		tmp = str[start];
		str[start] = str[end];
		str[end] = tmp;
		start++;
		end--;
	}
}
