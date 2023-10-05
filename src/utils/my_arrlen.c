/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** my_arrlen
*/

#include "../../include/include.h"

int my_arrlen(char **array)
{
    int length = 0;

    for (; array[length]; length++);
    return length;
}
