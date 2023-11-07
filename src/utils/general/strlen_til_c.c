/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** strlen_til_c
*/

#include "../../../include/include.h"

int my_strlen_til_c(char *str, char c)
{
    int lenght = 0;

    for (; str[lenght]; lenght++)
        if (str[lenght] == c)
            return lenght;
    return lenght;
}
