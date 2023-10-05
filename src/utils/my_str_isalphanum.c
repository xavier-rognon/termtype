/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** my_str_isalphanum
*/

#include "../../include/include.h"

bool my_char_isalphanum(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
        return true;
    return false;
}
