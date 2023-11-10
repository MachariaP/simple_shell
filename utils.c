#include "shell.h"

/**
 * free_2D_array - Frees the memory allocated for a 2D array.
 * @arr: The 2D array.
 */
void free_2D_array(char **arr)
{
    int i;

    if (!arr)
        return;

    for (i = 0; arr[i]; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }

    free(arr);
    arr = NULL;
}
