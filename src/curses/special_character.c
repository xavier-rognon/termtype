/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** special_character
*/

#include "../../include/include.h"
#include <curses.h>

void check_special_character(int row, int col, char to_check)
{
    switch (to_check) {
        case -69:
            mvprintw(row, col, "û");
            break;
        case -71:
            mvprintw(row, col, "ù");
            break;
        case -76:
            mvprintw(row, col, "ô");
            break;
        case -81:
            mvprintw(row, col, "ï");
            break;
        case -82:
            mvprintw(row, col, "î");
            break;
        case -86:
            mvprintw(row, col, "ê");
            break;
        case -87:
            mvprintw(row, col, "é");
            break;
        case -88:
            mvprintw(row, col, "è");
            break;
        case -89:
            mvprintw(row, col, "ç");
            break;
        case -94:
            mvprintw(row, col, "â");
            break;
        case -95:
            mvprintw(row, col, "á");
            break;
        case -96:
            mvprintw(row, col, "à");
            break;
        default:
            mvprintw(row, col, "%c", to_check);
            break;
    }
}
