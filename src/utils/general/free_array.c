/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** free_array
*/

#include "../../../include/include.h"

void free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
