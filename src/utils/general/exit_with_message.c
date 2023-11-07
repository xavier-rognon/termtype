/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** exit_with_message
*/

#include "../../../include/include.h"

void exit_with_message(char *message, int code)
{
    fprintf(stderr, "%s\n", message);
    exit(code);
}
