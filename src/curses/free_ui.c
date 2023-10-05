/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** free_ui
*/

#include "../../include/include.h"

void free_ui(ui_t *ui)
{
    free_parser(ui->parser);
    free(ui);
}
