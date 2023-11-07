/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** my_realloc
*/

#include "../../../include/include.h"

char **my_realloc(char **array, int lenght)
{
    char **new_array = malloc(sizeof(char *) * lenght + 1);

    for (int i = 0; i < lenght; i++) {
        if (i < my_arrlen(array))
            new_array[i] = strdup(array[i]);
        else
            new_array[i] = NULL;
    }
    free_array(array);
    return new_array;
}
