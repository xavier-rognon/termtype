/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** my_strcat
*/

#include "../../include/include.h"

int my_strlen(char *str)
{
    int length = 0;

    for (; str[length]; length++);
    return length;
}

char *my_strcat(char *str1, char *str2)
{
    char *new_str = malloc(sizeof(char) * (my_strlen(str1) + my_strlen(str2) + 1));
    int i = 0;

    for (; str1[i]; i++)
        new_str[i] = str1[i];
    for (int j = 0; str2[j]; j++, i++)
        new_str[i] = str2[j];
    new_str[i] = 0;
    return new_str;
}
