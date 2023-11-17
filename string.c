#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string, or NULL on failure.
 */
char *_strdup(const char *str)
{
	char *ptr;
	int i, len = 0;

	if (str == NULL)
		return NULL;

	while (*str != '\0')
	{
		len++;
		str++;
	}

	str = str - len;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		ptr[i] = str[i];

	return (ptr);
}
/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: The result of the comparison (0 if equal, positive/negative otherwise).
 */
int _strcmp(char *s1, char *s2)
{
	int cmp;

	cmp = (int)*s1 - (int)*s2;

	while (*s1)
	{
		if (*s1 != *s2)
			break;

		s1++;
		s2++;
		cmp = (int)*s1 - (int)*s2;
	}

	return (cmp);
}
/**
 * _strlen - Calculates the length of a string.
 * @s: The string.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)

{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}
/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the concatenated string.
 */
char *_strcat(char *dest, char *src)
{
	char *p = dest;

	if (dest == NULL || src == NULL)
		return dest;

	while (*p)
		p++;

	while (*src)
	{
		*p = *src;
		p++;
		src++;
	}

	*p = '\0'; /* add a null terminator at the end */
	return (dest);
}
/**
 * _strcpy - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the copied string.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == NULL || src == NULL)
		return dest; /* return dest unchanged if either pointer is NULL */

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0'; /* Add null terminator */
	return dest;
}
