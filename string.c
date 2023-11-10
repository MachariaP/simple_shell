#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string, or NULL on failure.
 */
char *string_duplicate(const char *str)
{
    char *duplicate;
    int i, length = 0;

    if (str == NULL)
        return NULL;

    while (*str != '\0')
    {
        length++;
        str++;
    }

    str = str - length;
    duplicate = malloc(sizeof(char) * (length + 1));
    if (duplicate == NULL)
        return NULL;

    for (i = 0; i <= length; i++)
        duplicate[i] = str[i];

    return duplicate;
}

/**
 * string_compare - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: The result of the comparison (0 if equal, positive/negative otherwise).
 */
int string_compare(char *s1, char *s2)
{
    int comparison;

    comparison = (int)*s1 - (int)*s2;
    while (*s1)
    {
        if (*s1 != *s2)
            break;
        s1++;
        s2++;
        comparison = (int)*s1 - (int)*s2;
    }

    return comparison;
}

/**
 * string_length - Calculates the length of a string.
 * @s: The string.
 *
 * Return: The length of the string.
 */
int string_length(char *s)
{
    int length = 0;

    while (s[length])
        length++;

    return length;
}

/**
 * string_concatenate - Concatenates two strings.
 * @destination: The destination string.
 * @source: The source string.
 *
 * Return: A pointer to the concatenated string.
 */
char *string_concatenate(char *destination, char *source)
{
    char *ptr = destination;

    if (destination == NULL || source == NULL)
        return destination;

    while (*ptr)
        ptr++;

    while (*source)
    {
        *ptr = *source;
        ptr++;
        source++;
    }

    *ptr = '\0'; /* add a null terminator at the end */
    return destination;
}

/**
 * string_copy - Copies a string.
 * @destination: The destination string.
 * @source: The source string.
 *
 * Return: A pointer to the copied string.
 */
char *string_copy(char *destination, char *source)
{
    int i = 0;

    if (destination == NULL || source == NULL)
        return destination;

    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }

    destination[i] = '\0'; /* Add null terminator */
    return destination;
}
