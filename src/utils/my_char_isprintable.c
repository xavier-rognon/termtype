/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** my_char_isalphanum
*/

#include "../../include/include.h"

bool my_char_isprintable(char c)
{
    if (!(c >= ' ' && c <= '~'))
        return false;
    return true;
}

