/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** clear_window
*/

#include "../../include/include.h"
#include <curses.h>

void clear_window(WINDOW *window)
{
    int x;
    int y;

    getmaxyx(window, y, x);
    for (int i = 1; i < y; i++)
        for (int j = 1; j < x; j++)
            mvwprintw(window, i, j, " ");
}
