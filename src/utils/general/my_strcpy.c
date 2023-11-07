/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** my_strdup
*/

#include "../../../include/include.h"

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    for (; src[i]; i++)
        dest[i] = src[i];
    dest[i] = 0;
    return dest;
}
