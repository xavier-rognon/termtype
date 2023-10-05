/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** my_show_word_array
*/

#include "../../include/include.h"

void my_show_word_array(char **array)
{
    for (int i = 0; array[i]; i++)
        printf("%s\n", array[i]);
}

void my_show_word_array_ncurses(char **array)
{
    for (int i = 0; array[i]; i++)
        printw("%s\n", array[i]);
}
